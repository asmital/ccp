# Group G45
# Date: 2021-03-06

[setup]

# Level number
let level_no = 1;

# Key binding for user input
keybind LEFT A;
keybind RIGHT D;
keybind CLOCKWISE P;
keybind ANTICLOCKWISE O;
keybind SOFT_DROP S;
keybind HARD_DROP W;
 
# Customise rewards 
SINGLE_LINE_REWARD=10*level_no;
DOUBLE_LINE_REWARD=20*level_no;
TRIPLE_LINE_REWARD=30*level_no;
TETRIS_LINE_REWARD=40*level_no;

# Boolean values to enable/disable soft and hard drop
SOFT_DROP_ON=true;
HARD_DROP_ON=true;

if SOFT_DROP_ON == true then SOFT_DROP_REWARD_MULTIPLIER = 1 endif; # 1*n, where n is the number of lines the tetromino is soft dropped
if HARD_DROP_ON == true then HARD_DROP_REWARD_MULTIPLIER = 2 endif; # 2*n, where n is the number of lines the tetromino is hard dropped
 
# End the game when 15 lines have been cleared, game doesnt end if a number of lines 
# have been cleared if this variable hasnt been set
LINES_TO_CLEAR=15;
# End game when a set time in seconds is over, game has no timer if this variable hasnt been set.
TIMER=50;

# Restrict program to 3x3 tetrominos, can extend later. 
# V I B G Y O R
# 1 2 3 4 5 6 7 
let block1 = [
        0, 0, 0,
        2,   2, 2,
        0, 2, 0
];

let block2 = [
        0, 1, 0,
        1, 1, 1, 
        1, 1, 1
];
 
let block3 = block1 * 3;
let block4 = block2 + block3;
 
NUM_TILES_X = 5;
NUM_TILES_Y = 20;
 
# Sequence of falling tetrominos follows a distibution based on these values
BAG = {block1:23, block2:26, block3:36, block4:72};
# Set positions of the blocks to follow a distribution proportional to these values for each block
POS = {1,3,4,1,1,2,2,1,1,5,6,7,3,4,5,6};

# Set a relative path to fetch background music and image
BGMUS="blah.mp3";
BGIMG="blah.jpg";

# The initial falling speed for the level
FALLING_SPEED=0.2;

[\setup] 
 
# everything in the update block gets executed every frame
[update]

TIMER = TIMER - 1;
FALLING_SPEED = FALLING_SPEED + TIMER/10; 
if SCORE == 10 then FALLING_SPEED = 100 endif;

[\update]
