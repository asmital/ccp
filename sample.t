
[setup]
let level_no = 1;


keybind LEFT A;
keybind RIGHT D; 

SINGLE_LINE_REWARD=10*level_no;


# Boolean values to enable/disable soft and hard drop
SOFT_DROP_ON=true;
HARD_DROP_ON=true;

LINES_TO_CLEAR=15;

TIMER=50;

# Restrict program to 3x3 tetrominos, can extend later. 
# V I B G Y O R
# 1 2 3 4 5 6 7 
let block1 = [
        0, 0, 0,
        2,   2, 2,
        0, 2, 0
] % 23;

let block2 = [
        0, 1, 0,
        1, 1, 1, 
        1, 1, 1
] % 26;
 
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
