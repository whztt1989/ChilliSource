//
//  TaskScheduler.cpp
//  ChilliSource
//  Created by Ian Copland on 05/04/2016.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2016 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#include <ChilliSource/Core/Threading/TaskSchedulerNew.h>

namespace ChilliSource
{
    namespace Core
    {
        CS_DEFINE_NAMEDTYPE(TaskSchedulerNew);
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        TaskSchedulerNewUPtr TaskSchedulerNew::Create() noexcept
        {
            //TODO: !? Implement
            return nullptr;
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        TaskSchedulerNew::TaskSchedulerNew() noexcept
        {
            //TODO: !? Implement
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        bool TaskSchedulerNew::IsA(CSCore::InterfaceIDType in_interfaceId) const noexcept
        {
            //TODO: !? Implement
            return false;
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        bool TaskSchedulerNew::IsMainThread() const noexcept
        {
            //TODO: !? Implement
            return false;
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void TaskSchedulerNew::ScheduleTask(TaskType in_taskType, const Task& in_task) noexcept
        {
            //TODO: !? Implement
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void TaskSchedulerNew::ScheduleTask(TaskType in_taskType, const SimpleTask& in_task) noexcept
        {
            //TODO: !? Implement
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void TaskSchedulerNew::ScheduleTasks(TaskType in_taskType, const std::vector<Task>& in_tasks, const Task& in_completionTask) noexcept
        {
            //TODO: !? Implement
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void TaskSchedulerNew::ScheduleTasks(TaskType in_taskType, const std::vector<SimpleTask>& in_tasks, const SimpleTask& in_completionTask) noexcept
        {
            //TODO: !? Implement
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void TaskSchedulerNew::WaitOnGameLogicTasks() noexcept
        {
            //TODO: !? Implement
        }
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
        void TaskSchedulerNew::ExecuteMainThreadTasks() noexcept
        {
            //TODO: !? Implement
        }
    }
}