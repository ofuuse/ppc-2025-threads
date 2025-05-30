#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "core/task/include/task.hpp"
#include "ref/sum_values_by_rows_matrix/include/ref_task.hpp"

TEST(sum_values_by_rows_matrix, check_int32_t) {
  // Create data
  std::vector<int32_t> in(1369, 2);
  std::vector<uint64_t> in_index(2, 37);
  std::vector<int32_t> out(37, 0);

  // Create task_data
  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  task_data->inputs_count.emplace_back(in.size());
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in_index.data()));
  task_data->inputs_count.emplace_back(in_index.size());
  task_data->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  task_data->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::reference::SumValuesByRowsMatrix<int32_t, uint64_t> test_task(task_data);
  bool is_valid = test_task.Validation();
  ASSERT_EQ(is_valid, true);
  test_task.PreProcessing();
  test_task.Run();
  test_task.PostProcessing();
  for (size_t i = 0; i < in_index[0]; i++) {
    ASSERT_EQ(static_cast<uint64_t>(out[0]), 2 * in_index[0]);
  }
}

TEST(sum_values_by_rows_matrix, check_validate_func1) {
  // Create data
  std::vector<int32_t> in(1369, 2);
  std::vector<uint64_t> in_index(2, 37);
  std::vector<int32_t> out(39, 0);

  // Create task_data
  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  task_data->inputs_count.emplace_back(in.size());
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in_index.data()));
  task_data->inputs_count.emplace_back(in_index.size());
  task_data->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  task_data->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::reference::SumValuesByRowsMatrix<int32_t, uint64_t> test_task(task_data);
  bool is_valid = test_task.Validation();
  ASSERT_EQ(is_valid, false);
}

TEST(sum_values_by_rows_matrix, check_validate_func2) {
  // Create data
  std::vector<int32_t> in(1369, 2);
  std::vector<uint64_t> in_index(3, 37);
  std::vector<int32_t> out(37, 0);

  // Create task_data
  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  task_data->inputs_count.emplace_back(in.size());
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in_index.data()));
  task_data->inputs_count.emplace_back(in_index.size());
  task_data->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  task_data->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::reference::SumValuesByRowsMatrix<int32_t, uint64_t> test_task(task_data);
  auto is_valid = test_task.Validation();
  ASSERT_EQ(is_valid, false);
}

TEST(sum_values_by_rows_matrix, check_double) {
  // Create data
  std::vector<double> in(1406, 1.0 / 38.0);
  std::vector<uint64_t> in_index = {37, 38};
  std::vector<double> out(37, 0);

  // Create task_data
  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  task_data->inputs_count.emplace_back(in.size());
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in_index.data()));
  task_data->inputs_count.emplace_back(in_index.size());
  task_data->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  task_data->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::reference::SumValuesByRowsMatrix<double, uint64_t> test_task(task_data);
  bool is_valid = test_task.Validation();
  ASSERT_EQ(is_valid, true);
  test_task.PreProcessing();
  test_task.Run();
  test_task.PostProcessing();
  for (size_t i = 0; i < in_index[0]; i++) {
    EXPECT_NEAR(out[i], 1.0, 1e-6);
  }
}

TEST(sum_values_by_rows_matrix, check_int8_t) {
  // Create data
  std::vector<int8_t> in(1406);
  std::vector<uint64_t> in_index = {37, 38};
  std::vector<int8_t> out(37, 0);
  for (size_t i = 0; i < in.size(); ++i) {
    in[i] = (i % 2) != 0 ? -2 : 2;
  }

  // Create task_data
  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  task_data->inputs_count.emplace_back(in.size());
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in_index.data()));
  task_data->inputs_count.emplace_back(in_index.size());
  task_data->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  task_data->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::reference::SumValuesByRowsMatrix<int8_t, uint64_t> test_task(task_data);
  bool is_valid = test_task.Validation();
  ASSERT_EQ(is_valid, true);
  test_task.PreProcessing();
  test_task.Run();
  test_task.PostProcessing();
  for (size_t i = 0; i < in_index[0]; i++) {
    ASSERT_EQ(out[0], 0);
  }
}

TEST(sum_values_by_rows_matrix, check_int64_t) {
  // Create data
  std::vector<int64_t> in(1406);
  std::vector<uint64_t> in_index = {37, 38};
  std::vector<int64_t> out(37, 0);
  for (size_t i = 0; i < in.size(); ++i) {
    in[i] = static_cast<int64_t>((i % 38) + 1);
  }

  // Create task_data
  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  task_data->inputs_count.emplace_back(in.size());
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in_index.data()));
  task_data->inputs_count.emplace_back(in_index.size());
  task_data->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  task_data->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::reference::SumValuesByRowsMatrix<int64_t, uint64_t> test_task(task_data);
  bool is_valid = test_task.Validation();
  ASSERT_EQ(is_valid, true);
  test_task.PreProcessing();
  test_task.Run();
  test_task.PostProcessing();
  for (size_t i = 0; i < in_index[0]; i++) {
    ASSERT_EQ(out[0], static_cast<int64_t>(in_index[1] * (in_index[1] + 1)) / 2);
  }
}

TEST(sum_values_by_rows_matrix, check_float) {
  // Create data
  std::vector<float> in(1406);
  std::vector<uint64_t> in_index = {37, 38};
  std::vector<float> out(37, 0.F);
  for (size_t i = 0; i < in.size(); ++i) {
    in[i] = static_cast<float>((i % 38) + 1);
    in[i] *= in[i];
  }

  // Create task_data
  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in.data()));
  task_data->inputs_count.emplace_back(in.size());
  task_data->inputs.emplace_back(reinterpret_cast<uint8_t*>(in_index.data()));
  task_data->inputs_count.emplace_back(in_index.size());
  task_data->outputs.emplace_back(reinterpret_cast<uint8_t*>(out.data()));
  task_data->outputs_count.emplace_back(out.size());

  // Create Task
  ppc::reference::SumValuesByRowsMatrix<float, uint64_t> test_task(task_data);
  bool is_valid = test_task.Validation();
  ASSERT_EQ(is_valid, true);
  test_task.PreProcessing();
  test_task.Run();
  test_task.PostProcessing();
  for (size_t i = 0; i < in_index[0]; i++) {
    EXPECT_NEAR(out[i], in_index[1] * (in_index[1] + 1) * (2 * in_index[1] + 1) / 6.F, 1e-6);
  }
}
