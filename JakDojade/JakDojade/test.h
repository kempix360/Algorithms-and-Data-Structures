/*
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
0
3
KIELCE KRAKOW 0
KRAKOW GDANSK 0
KRAKOW GDANSK 1

    clock_t startTime4 = clock(), endTime4;
    double time_taken4;

    endTime4 = clock();
    time_taken4 = double(endTime4 - startTime4) / double(CLOCKS_PER_SEC);
    cout << "Compilation time 4: " << time_taken4 << " s" << endl;
*/