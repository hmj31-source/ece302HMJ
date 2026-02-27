#ifndef _SORT_HPP
#define _SORT_HPP

#include "List.hpp"

template<typename T> 
inline void quick_sort(List<T>& list, int first, int last)
{
	// TODO
	if (first >= last) return;
	int pivotIndex = partition(list, first, last);
	quick_sort(list, first, pivotIndex - 1);
	quick_sort(list, pivotIndex + 1, last);

}

/** Partition a sub-list by moving items relative to the pivot.
 * Always choose the first item as the pivot.
 * Sub-list is specified with inclusive indices first and last.
 * Assume no duplicates.
 * @param first index of the first item in the sub-list to be partitioned (inclusive)
 * @param last index of the last item in the sub-list to be partitioned (inclusive)
 * @return index of the pivot item after partitioning */
template <typename T>
inline int partition(List<T>& list, int first, int last) {
	// TODO
	T pivot = list.getEntry((std::size_t)first);
	int storeIndex = first;

	for (int j = first + 1; j <= last; ++j){
		T cur = list.getEntry((std::size_t)j);
		if (cur < pivot){
			++storeIndex;
			//move item
			list.moveEntry((std::size_t)j, (std::size_t)storeIndex);
		}
	}
	list.moveEntry((std::size_t)first, (std::size_t)storeIndex);

	return storeIndex;
}

#endif
