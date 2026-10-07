# The stage overlays

Each stage overlay, AAA/PRO/WSTAG###.PRO, is one C file, `wstag###.c`, in
the folder of the area that FIELDSTG names when the player enters it
(FIELDSTG_stages gives a stage its modes, FIELDSTG_areaNames a mode its
area, a string of text file 0xAA). `tools/stage_areas.py` moves them and
writes this list.

- `common/` holds the code that several stages share, which they include.
- `wstag260.c`, the story events' scripts, belongs to no area: no mode
  starts it, FIELDSTG runs its scripts.

The cities have two copies of their stages, one for each server (Asuka and
Amaterasu, Seiryu and Qing Long, Suzaku and Zhu Que, Byakko and Bai Hu),
and the European version adds stages of its own (920 and up) to the areas.

| Folder | Area | Stages | WSTAG |
|---|---|---|---|
| `central_sector/` | Central Sector | 23 | 200, 201, 202, 203, 205, 206, 218, 219, 330, 331, 335, 336, 340, 341, 345, 346, 920, 921, 922, 940, 941, 942, 943 |
| `asuka_city/` | Asuka City | 24 | 210, 212, 220, 225, 230, 232, 235, 237, 240, 245, 250, 255, 270, 275, 280, 285, 290, 295, 300, 305, 310, 315, 320, 325 |
| `amaterasu_city/` | Amaterasu City | 41 | 211, 221, 226, 231, 233, 236, 238, 241, 246, 251, 256, 261, 271, 276, 281, 286, 291, 296, 301, 306, 311, 316, 321, 326, 923, 924, 925, 926, 927, 928, 929, 930, 931, 932, 933, 934, 935, 936, 937, 938, 939 |
| `east_sector/` | East Sector | 40 | 350, 351, 355, 356, 360, 361, 365, 366, 370, 371, 375, 376, 380, 381, 385, 386, 395, 396, 400, 401, 405, 406, 410, 411, 415, 420, 421, 944, 945, 946, 947, 948, 949, 950, 951, 952, 953, 954, 955, 956 |
| `seiryu_city/` | Seiryu City | 3 | 425, 430, 435 |
| `qing_long_city/` | Qing Long City | 6 | 426, 431, 436, 957, 958, 959 |
| `south_sector/` | South Sector | 32 | 440, 441, 445, 446, 450, 451, 455, 456, 460, 465, 466, 470, 471, 475, 476, 480, 481, 485, 486, 490, 491, 495, 496, 500, 501, 525, 526, 530, 531, 535, 537, 538 |
| `suzaku_city/` | Suzaku City | 2 | 505, 520 |
| `zhu_que_city/` | Zhu Que City | 2 | 506, 521 |
| `network_break/` | Network Break | 2 | 540, 545 |
| `west_sector/` | West Sector | 45 | 550, 551, 555, 556, 560, 561, 565, 566, 570, 571, 575, 576, 580, 581, 585, 586, 590, 591, 595, 596, 600, 601, 605, 606, 610, 611, 615, 616, 620, 621, 625, 630, 631, 635, 636, 640, 641, 645, 646, 650, 651, 655, 656, 660, 661 |
| `byakko_city/` | Byakko City | 3 | 675, 680, 685 |
| `bai_hu_city/` | Bai Hu City | 2 | 676, 686 |
| `north_sector/` | North Sector | 29 | 690, 691, 695, 696, 700, 701, 705, 706, 710, 711, 715, 716, 720, 721, 725, 726, 730, 731, 735, 736, 740, 741, 745, 746, 750, 755, 756, 760, 761 |
| `kusanagi_city/` | Kusanagi City | 3 | 780, 785, 790 |
| `undersea_base/` | Undersea Base | 3 | 795, 800, 805 |
| `spy_satellite/` | Spy Satellite | 3 | 810, 815, 820 |
| `underground/` | Underground | 30 | 825, 830, 835, 840, 845, 850, 855, 860, 865, 870, 875, 880, 885, 890, 895, 960, 961, 962, 963, 964, 965, 966, 967, 968, 969, 970, 971, 972, 973, 974 |
