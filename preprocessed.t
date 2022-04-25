[setup]
let level_no = 1;
keybind LEFT A;
keybind RIGHT D;
SINGLE_LINE_REWARD=10*level_no;
SOFT_DROP_ON=true;
HARD_DROP_ON=true;
LINES_TO_CLEAR=15;
TIMER=50;
let block1 = [
0, 0, 0,
2, 2, 2,
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
BAG = {block1:23, block2:26, block3:36, block4:72};
POS = {1,3,4,1,1,2,2,1,1,5,6,7,3,4,5,6};
BGMUS="blah.mp3";
BGIMG="blah.jpg";
FALLING_SPEED=0.2;
[\setup]
[update]
TIMER = TIMER - 1;
FALLING_SPEED = FALLING_SPEED + TIMER/10;
if SCORE == 10 then FALLING_SPEED = 100 endif;
[\update]
