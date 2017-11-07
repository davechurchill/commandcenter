#pragma once
#include <stack>
#include <string>
#include <iostream>
#include <assert.h>
#include "Behavior.h"

class BehaviorTree
{
protected:
    Behavior* m_pRoot;
public:
    BehaviorTree(Behavior* b)
    {
        m_pRoot = b;
    }
    void tick() {
        m_pRoot->tick();
    }
};

// from https://michaelyagidotcom.wordpress.com/behavior-tree-builder/
template <class parent_type>
class NodeBuilder;

template <class parent_type>
class LeafBuilder {
public:
    LeafBuilder(parent_type* parent, Behavior* leaf) :
        m_parent(parent),
        m_leaf(leaf) {}

    parent_type& end()
    {
        return *m_parent;
    }
private:
    parent_type* m_parent;
    Behavior* m_leaf;
};

template <class parent_type>
class NodeBuilder {
public:
    NodeBuilder(parent_type* parent, Composite* node):
        m_parent(parent),
        m_node(node) {}

    LeafBuilder<NodeBuilder<parent_type>> action(Behavior * action) {
        m_node->addChild(action);
        return LeafBuilder<NodeBuilder<parent_type>>(this, action);
    }

    LeafBuilder<NodeBuilder<parent_type>> condition(Behavior * condition) {
        m_node->addChild(condition);
        return LeafBuilder<NodeBuilder<parent_type>>(this, condition);
    }

    NodeBuilder<NodeBuilder<parent_type>> selector() {
        Selector* selector = new Selector();
        m_node->addChild(selector);
        return NodeBuilder<NodeBuilder<parent_type>>(this, selector);
    }

    NodeBuilder<NodeBuilder<parent_type>> sequence() {
        Sequence* sequence = new Sequence();
        m_node->addChild(sequence);
        return NodeBuilder<NodeBuilder<parent_type>>(this, sequence);
    }

    parent_type& end()
    {
        return *m_parent;
    }

private:
    parent_type* m_parent;
    Composite* m_node;
};

class BehaviorTreeBuilder {

protected:
    Behavior* m_parentNode;

public:
    virtual ~BehaviorTreeBuilder() {}
    BehaviorTreeBuilder() {}

    LeafBuilder<BehaviorTreeBuilder> action(Behavior * action) {
        m_parentNode = action;
        return LeafBuilder<BehaviorTreeBuilder>(this, action);
    }

    LeafBuilder<BehaviorTreeBuilder> condition(Behavior * condition) {
        m_parentNode = condition;
        return LeafBuilder<BehaviorTreeBuilder>(this, condition);
    }

    NodeBuilder<BehaviorTreeBuilder> sequence() {
        Sequence* sequence = new Sequence();
        m_parentNode = sequence;
        return NodeBuilder<BehaviorTreeBuilder>(this, sequence);
    }
    NodeBuilder<BehaviorTreeBuilder> selector() {
        Selector* selector = new Selector();
        m_parentNode = selector;
        return NodeBuilder<BehaviorTreeBuilder>(this, selector);
    }

    BehaviorTree* end()
    {
        return new BehaviorTree(m_parentNode);
    }   
};

