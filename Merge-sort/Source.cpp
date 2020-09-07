#include <vector>
#include <iostream>
#include <chrono>
#include <cstdlib>

void merge(std::vector<int> &vec, size_t begin, size_t middle, size_t end)
{
	size_t vec_l_size = middle - begin + 1;
	size_t vec_r_size = end - middle;

	std::vector<int> vec_l;
	vec_l.reserve(vec_l_size);
	for (size_t i = 0; i < vec_l_size; ++i)
		vec_l.push_back(vec[begin + i]);

	std::vector<int> vec_r;
	vec_r.reserve(vec_r_size);
	for (size_t i = 0; i < vec_r_size; ++i)
		vec_r.push_back(vec[middle + 1 + i]);

	size_t i = 0, j = 0, pos = begin;
	while ((i < vec_l.size()) && (j < vec_r.size()))
		vec[pos++] = vec_l[i] <= vec_r[j] ? vec_l[i++] : vec_r[j++];

	while (i < vec_l.size())
		vec[pos++] = vec_l[i++];
	while (j < vec_r.size())
		vec[pos++] = vec_r[j++];
}

void sort(std::vector<int> &vec, size_t begin, size_t end)
{
	if (begin < end)
	{
		size_t middle = (end + begin) / 2;

		sort(vec, begin, middle);
		sort(vec, middle + 1, end);

		merge(vec, begin, middle, end);
	}
}

int main()
{
	std::vector<int> vec;
	size_t vec_size = 10;
	for (size_t i = 0; i < vec_size; ++i)
		vec.emplace_back(rand());
	std::cout << "Vector values: ";
	for (const auto &v : vec)
		std::cout << v << '\t';
	
	
	auto t1 = std::chrono::high_resolution_clock::now();
	sort(vec, 0, 7);
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<float, std::milli>(t2 - t1);
	std::cout << "\nMerge sort took [" << duration.count() << "ms]\n"
		<< "After Merge sort: ";
	for (const auto &v : vec)
		std::cout << v << '\t';
	
	std::cin.get();
}