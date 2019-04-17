// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskNode.h"


TaskNode::~TaskNode()
{
}

TSharedPtr<TaskNode> TaskNode::GetNextTaskNode()
{
    if(NextTaskNode.IsValid())
        return NextTaskNode;
    else    
        return nullptr;    
}

void TaskNode::SetNextTaskNode(TSharedPtr<TaskNode> Node)
{
    NextTaskNode = Node;    
}

