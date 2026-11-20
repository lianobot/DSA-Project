# Team lead checklist (Member 1)

## Before you send the hand-offs
- [ ] Open the folder in Visual Studio (File > Open > Folder). It builds with **zero warnings** (the stubs already do).
- [ ] Create the GitHub repo, push this folder, add the 3 teammates, and have each clone it. First commit message: `Kickoff scaffold`.
- [ ] Register team of 4 at kickoff with roles from `README.md` (the handout marks CLO5 against the role you record).
- [ ] Send each teammate their `docs/HANDOFF_*.md` plus the repo link. They only edit their own `.cpp` (and add tests at the marked spot in their test file).
- [ ] Write **your own** `src/LinkedList.cpp` (stub is there; `test_linkedlist` must go green). Do not skip this - it is yours to explain in the viva.
- [ ] Optional: ask teammates to work on a branch and open a pull request into `main`; you review and merge (keeps history clean and shows collaboration).

## Order things turn green
1. `test_linkedlist` (you, Checkpoint 1 - end Wk 11) - then `test_loader` turns green once the other pieces exist.
2. `test_ranking` (M3, Checkpoint 2 - end Wk 13). The last 2 tests need your LinkedList.
3. `test_hashtable` (M2, Checkpoint 3 - Wk 15 lab).
4. `test_graph` (M4, by end Wk 15).
5. `test_loader` and `test_integration` - **all green = components work together**.
Tip: until a teammate pushes, their test file simply fails; ignore it. Never "fix" a teammate's test to make it pass.

## When a teammate pushes
1. Pull. Build. Open the Error List - any `/W4` warning in their file goes back to them.
2. Run **only their** test file first. Then the whole suite (Test Explorer).
3. A failing test is almost always in the new code. If you believe the **test** is wrong, check the header's contract first, then change the test and tell everyone.

## Before every checkpoint and the final (WSL / Git Bash)
- [ ] `bash tools/check_rules.sh` -> `ALL CHECKS PASSED` (banned-STL scan, strict g++ `-Wall -Wextra -fsanitize=address,undefined` build, every test under the sanitizers). The graders compile this way even though you develop in Visual Studio.
- [ ] In Visual Studio: run `social_app` and look at the Output window - no memory-leak report after exit.
- [ ] `git log` shows commits from **every** member across the weeks (the handout marks this).

## Final week
- [ ] Release build (x64 Release), run `bench_timing`, give M2 the output for the report.
- [ ] Assemble `docs/REPORT_TEMPLATE.md` into the report: complexity table, trade-offs for **all four** components (what you give up, not just why it was right), exactly one timing table, honest "what does not work" paragraph, attribution (lab code, teammates, AI use), one paragraph per member.
- [ ] Everyone rehearses their own part + viva (3-5 min each): explain your code, explain how it connects to teammates', live-modify something small.
- [ ] Late days: the team can only use the **lowest** remaining balance among members.

## Handout self-check mapping
| Handout item | Where it is covered |
|---|---|
| 1, 3 compiles clean, no STL | `tools/check_rules.sh` |
| 4, 5 duplicate ID / unknown-ID edge rejected | `test_loader` |
| 6 forced collision | `test_hashtable::test_forced_collision_is_handled` |
| 7 hash and list agree | `test_integration::test_hash_agrees_with_list` |
| 8 BFS = hand set | `test_integration::test_bfs_matches_expected_sets` |
| 9 ranking = hand answer | `test_integration::test_ranking_matches_expected` |
| 11 one timing comparison | `bench_timing` |
| 10, 12, 13, 14, 15, 16 | report (template) and viva rehearsal |

Edge cases required by the handout: empty dataset (`test_loader`, `test_linkedlist`, `test_graph`, `test_ranking`), single record (`test_linkedlist`), duplicate ID (`test_linkedlist`, `test_loader`), missing ID lookup (`test_linkedlist`, `test_hashtable`), forced collision (`test_hashtable`).
