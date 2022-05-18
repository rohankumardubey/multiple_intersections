/*
 * Copyright Max De Marzi. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "benchmark/benchmark.h"
#include "generate_data.h"

#include <set>
#include <vector>
#include <algorithm>





std::vector<uint64_t> using_ranges_multi_set_intersection(std::vector<std::vector<uint64_t>>& nums) {

    // 1. Check if any index is empty, if so then the intersection is empty
    for (auto& index : nums) {
        if (index.empty()) {
            return {};
        }
    }

    // 2. Sort indexes by their first value
    std::sort(nums.begin(), nums.end());

    // 3. Swap the 2nd vector for the last one to try to eliminate a bunch right away
    nums.at(1).swap(nums.at(nums.size() - 1));

    // initialize by the first vector
    std::vector<uint64_t> result(nums[0].begin(), nums[0].end());

    for (int i = 1; i < nums.size(); ++i) {
        std::vector<uint64_t> intersection;
        std::ranges::set_intersection(nums[i], result, back_inserter(intersection));
        result = intersection;
    }

    return result;
}

static void BM_using_ranges_multi_set_intersection(benchmark::State &state) {
    sorted_vectors = sorted_maps[state.range(0)][state.range(1)];
    for (auto _ : state) {
        benchmark::DoNotOptimize(using_ranges_multi_set_intersection(sorted_vectors));
    }
}



BENCHMARK(BM_using_ranges_multi_set_intersection)
    ->ArgsProduct({benchmark::CreateDenseRange(2, 7, /*step=*/ 1),
                   benchmark::CreateRange(8, 262144, /*multi=*/ 8)})
        ->Setup(load_data);

BENCHMARK_MAIN();