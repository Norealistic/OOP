#ifndef maps_hpp
#define maps_hpp

#define LINE_QUANTITY 20
#include <cstring>
#include <iostream>


typedef struct square{
    std::string lines[LINE_QUANTITY];
} square;

static square map_catalog[3] = {
{"########################################", "###########...............&............<", "###########.............................", "###########.............................", "########################................", "##############.....&...#................", "##############.........#................", "<............#.........#......##########", ".............#.........#......#..&....##", "###########..#.........#......#.......##", "###########..#####+#####......+.......##", "###########...................#.......##", "###########...................##########", "############+##############+############", "############.##########.&.......########", "########.....##########.........########", "###..&.......##########.........########", "###..........##########.........########", "###.....###############.........########", "########################################"},
{"########################################", "###########...&......#....&............<", "###########..........+..................", "###########....#######........##########", "########################......#........#", "##############.....&...#......+.......&#", "##############.........#......#........#", "<............#.........#......##########", ".............#.........#......#..&....##", "###########..#.........#......#.......##", "###########..#####+#####......+.......##", "##.&..#####...................#.......##", "##....#####...................##########", "##....######+##############+############", "###..#######.##########.&.......########", "###..###.....##########.........########", "###..&.......##########........&########", "###..........##########.........########", "###.....###############.&.......########", "########################################"},
{"########################################", "#############....&&......&&..#.........<", "#############................#.........#", "#############................#.........#", "###################+##########.........#", "######.................................#", "######.................................#", "<........############...############...#", ".........#....#.....#...#....#.....#...#", "######...+....#&....+...+....#&....+...#", "#..&.#...#..&.#.....#...#..&.#.....#...#", "#&...+...############...############...#", "#....#...#...&#..&..#...#...&#..&..#...#", "######...+....#.....+...+....#.....+...#", "#..&.#...#....#..&..#...#....#..&..#...#", "#&...#...############...############...#", "#....#...######&....#...#...&#..&..#...#", "###############.....+...+....#.....+...#", "###############&....#...#..&.#.....#...#", "########################################"}};


typedef enum level_numbers {LEVEL_1, LEVEL_2, LEVEL_3} level_numbers;

static void map_output(square &map){
    
    for (int i = 0; i < LINE_QUANTITY; i++)
        std::cout << map.lines[i] << std::endl;
}
#endif /* maps_hpp */

