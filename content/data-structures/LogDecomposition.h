/**
 * Author: ismailfateen
 * Date: 2009-10-30
 * License: CC0
 * Source: Codeforces
 * Description: Technique to insert random elements into sorted data structures
 * Status: Stress-tested
 */
DS merge(DS& a, DS& b) {
 // This function merges the 2 sorted data structures. This would depend on how the data structure works.
}
void insert(T element) {
  DS current;
  current.insert(element);
  int index = 0;
  while (blk[index].size > 0) {
   current = merge(current, blk[index]), blk[index].clear();
   index++;
  }
  blk[index] = current;
}