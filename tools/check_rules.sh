#!/usr/bin/env bash
# Run from the project root in WSL / Git Bash / Linux:  bash tools/check_rules.sh
# Mirrors the handout's self-check items 1 and 3 (the graders compile with g++).
set -u
fail=0
COMPONENT_FILES="src/LinkedList.h src/LinkedList.cpp src/HashTable.h src/HashTable.cpp src/Graph.h src/Graph.cpp src/Ranking.h src/Ranking.cpp src/Queue.h src/Stack.h"

echo "== 1. Banned STL containers in Components 1-4 =="
if grep -nE '#include *<(vector|list|deque|stack|queue|map|unordered_map|set|unordered_set|priority_queue|array|forward_list|algorithm)>|std::(vector|list|deque|stack|queue|map|unordered_map|set|priority_queue)\b|std::sort' $COMPONENT_FILES; then
  echo "FOUND banned STL use above (comments count too - reword them)"; fail=1
else echo "OK - none found"; fi

echo; echo "== 2. new / delete count per file (rough leak hint, not proof) =="
for f in src/LinkedList.cpp src/HashTable.cpp src/Graph.cpp src/Ranking.cpp src/Loader.cpp; do
  printf "%-22s new: %s   delete: %s\n" "$f" "$(grep -cE '\bnew\b' $f)" "$(grep -cE '\bdelete\b' $f)"
done

echo; echo "== 3. Strict build: g++ -Wall -Wextra -fsanitize=address,undefined =="
mkdir -p build_strict
SRC="src/LinkedList.cpp src/HashTable.cpp src/Graph.cpp src/Ranking.cpp src/Loader.cpp"
for t in test_linkedlist test_hashtable test_graph test_ranking test_loader test_integration; do
  out=$(g++ -std=c++17 -Wall -Wextra -fsanitize=address,undefined -g -Isrc -DDATA_DIR="\"$PWD/data\"" $SRC tests/$t.cpp -o build_strict/$t 2>&1)
  if [ -n "$out" ]; then echo "--- warnings/errors building $t:"; echo "$out"; fail=1; fi
done
out=$(g++ -std=c++17 -Wall -Wextra -fsanitize=address,undefined -g -Isrc -DDATA_DIR="\"$PWD/data\"" $SRC src/main.cpp -o build_strict/social_app 2>&1)
if [ -n "$out" ]; then echo "--- warnings/errors building social_app:"; echo "$out"; fail=1; fi

echo; echo "== 4. Run every test under the sanitizers (any leak / memory error shows here) =="
for t in test_linkedlist test_hashtable test_graph test_ranking test_loader test_integration; do
  if [ -x build_strict/$t ]; then
    res=$(timeout 60 build_strict/$t 2>&1); rc=$?
    echo "$t: $(echo "$res" | grep -E 'passed,' )"
    if [ $rc -ne 0 ]; then fail=1; echo "$res" | grep -E 'FAIL|Sanitizer|ERROR|leak' | head -8; fi
  fi
done

echo; if [ $fail -eq 0 ]; then echo "ALL CHECKS PASSED"; else echo "SOME CHECKS FAILED - see above"; fi
exit $fail
