/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <gtest/gtest.h>
#include <string>

#include "cyber/cyber.h"
#include "cyber/scheduler/scheduler.h"
#include "cyber/common/global_data.h"

namespace apollo {
namespace cyber {
namespace scheduler {

auto sched = Scheduler::Instance();

void proc() {}

TEST(SchedulerTest, create_task) {
  cyber::Init();
  std::string croutine_name = "DriverProc";
  sched->RtCtx().clear();
  EXPECT_TRUE(sched->CreateTask(&proc, croutine_name));
  // create a croutine with the same name
  EXPECT_FALSE(sched->CreateTask(&proc, croutine_name));
  auto task_id = GlobalData::RegisterTaskName(croutine_name);
  EXPECT_TRUE(sched->NotifyTask(task_id));
  EXPECT_TRUE(sched->RemoveTask(croutine_name));
  sched->ShutDown();
  EXPECT_FALSE(sched->CreateTask(&proc, croutine_name));
}

}  // namespace scheduler
}  // namespace cyber
}  // namespace apollo