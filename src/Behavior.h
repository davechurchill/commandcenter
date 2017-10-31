#pragma once
#include <vector>

// Taken from https://github.com/aigamedev/btsk/blob/master/BehaviorTree.cpp

enum Status
{
	BH_INVALID,
	BH_SUCCESS,
	BH_FAILURE,
	BH_RUNNING,
	BH_ABORTED,
};

class Behavior
{
public:

	Behavior() : m_eStatus(BH_INVALID) {}
	virtual ~Behavior() {}

	virtual Status update() = 0;
	virtual void onInitialize() {};
	virtual void onTerminate(Status) {};

	Status tick()
	{
		if (m_eStatus != BH_RUNNING) onInitialize();
		m_eStatus = update();
		if (m_eStatus != BH_RUNNING) onTerminate(m_eStatus);
		return m_eStatus;
	};
	void reset() { m_eStatus = BH_INVALID; }
	void abort()
	{
		onTerminate(BH_ABORTED);
		m_eStatus = BH_ABORTED;
	}

	bool isTerminated() const { return m_eStatus == BH_SUCCESS || m_eStatus == BH_FAILURE; }
	bool isRunning() const { return m_eStatus == BH_RUNNING; }
	Status getStatus() const { return m_eStatus; }
private:
	Status m_eStatus;
};

class ConditionAction : public Behavior {
protected:
    bool condition;

public:
    ConditionAction(bool pred) : condition(pred) {}
    virtual Status update() override { return condition ? Status::BH_SUCCESS : Status::BH_FAILURE; }
};

class Decorator : public Behavior
{
protected:
	Behavior* m_pChild;

public:
	Decorator(Behavior* child) : m_pChild(child) {}
};

class Repeat : public Decorator
{
public:
	Repeat(Behavior* child, size_t count) : Decorator(child) { m_iLimit = count; }
	void onInitialize() { m_iCounter = 0; }
	Status update()
	{
        for (size_t i = 0; i < m_iLimit; ++i) 
        {
            if (m_pChild->tick() != BH_SUCCESS)
                break;
        }
        return m_pChild->getStatus();
	}

protected:
    size_t m_iLimit;
    size_t m_iCounter;
};

class Composite : public Behavior
{
public:
	void addChild(Behavior* child) { m_Children.push_back(child); }
    void removeChild(Behavior*) { };
    void clearChildren() { };
protected:
	typedef std::vector<Behavior*> Behaviors;
	Behaviors m_Children;
};

class Sequence : public Composite
{
public:
    virtual ~Sequence() {}

protected:
	virtual void onInitialize()
	{
		m_CurrentChild = m_Children.begin();
	}

	virtual Status update()
	{
		// Keep going until a child behavior says it's running.
		while (true)
		{
			Status s = (*m_CurrentChild)->tick();

			// If the child fails, or keeps running, do the same.
			if (s != BH_SUCCESS) return s;

			// Hit the end of the array, job done!
			if (++m_CurrentChild == m_Children.end()) return BH_SUCCESS;
		}
	}

	Behaviors::iterator m_CurrentChild;
};

class Selector : public Composite
{
public:
    virtual ~Selector() {}

protected:
	virtual void onInitialize() { m_Current = m_Children.begin(); }

	virtual Status update()
	{
		// Keep going until a child behavior says its running.
        while (true)
		{
			Status s = (*m_Current)->tick();

			// If the child succeeds, or keeps running, do the same.
			if (s != BH_FAILURE) return s;

			// Hit the end of the array, it didn't end well...
			if (++m_Current == m_Children.end()) return BH_FAILURE;
		}
	}

	Behaviors::iterator m_Current;
};

class Parallel : public Composite
{
public:
	enum Policy
	{
		RequireOne,
		RequireAll,
	};

	Parallel(Policy forSuccess, Policy forFailure)
		: m_eSuccessPolicy(forSuccess)
		, m_eFailurePolicy(forFailure)
	{
	}

	virtual ~Parallel() {}

protected:
	Policy m_eSuccessPolicy;
	Policy m_eFailurePolicy;

	virtual Status update()
	{
		size_t iSuccessCount = 0, iFailureCount = 0;

		for (Behaviors::iterator it = m_Children.begin(); it != m_Children.end(); ++it)
		{
			Behavior& b = **it;
			if (!b.isTerminated())
			{
				b.tick();
			}

			if (b.getStatus() == BH_SUCCESS)
			{
				++iSuccessCount;
				if (m_eSuccessPolicy == RequireOne)
				{
					return BH_SUCCESS;
				}
			}

			if (b.getStatus() == BH_FAILURE)
			{
				++iFailureCount;
				if (m_eFailurePolicy == RequireOne)
				{
					return BH_FAILURE;
				}
			}
		}

		if (m_eFailurePolicy == RequireAll  &&  iFailureCount == m_Children.size())
		{
			return BH_FAILURE;
		}

		if (m_eSuccessPolicy == RequireAll  &&  iSuccessCount == m_Children.size())
		{
			return BH_SUCCESS;
		}

		return BH_RUNNING;
	}

	virtual void onTerminate(Status)
	{
		for (Behaviors::iterator it = m_Children.begin(); it != m_Children.end(); ++it)
		{
			Behavior& b = **it;
			if (b.isRunning())
			{
				b.abort();
			}
		}
	}
};

class Monitor : public Parallel
{
public:
	Monitor()
		: Parallel(Parallel::RequireOne, Parallel::RequireOne)
	{
	}

	void addCondition(Behavior* condition)
	{
		m_Children.insert(m_Children.begin(), condition);
	}

	void addAction(Behavior* action)
	{
		m_Children.push_back(action);
	}
};

class ActiveSelector : public Selector
{
protected:

	virtual void onInitialize()
	{
		m_Current = m_Children.end();
	}

	virtual Status update()
	{
		Behaviors::iterator previous = m_Current;

		Selector::onInitialize();
		Status result = Selector::update();

		if (previous != m_Children.end() && m_Current != previous)
		{
			(*previous)->onTerminate(BH_ABORTED);
		}
		return result;
	}
};

class BehaviorTree
{
protected:
    Behavior* m_pRoot;
public:
    virtual void tick() {};
};

class ActionVerbose : public Behavior {
private:
    std::string name;
public:
    ActionVerbose(const std::string n) : name(n) {}
private:
    Status update() {
        std::cout << name << " succeeded." << std::endl;
        return Status::BH_SUCCESS;
    }
};

class RangedBehaviorTree : public BehaviorTree
{
public:
    RangedBehaviorTree(Behavior* b)
    {
        m_pRoot = b;
    }
    void tick() {
        m_pRoot->tick();
    }
};

