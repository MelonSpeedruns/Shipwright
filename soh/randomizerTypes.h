#pragma once

typedef struct {
    char tex[512];
    uint16_t width;
    uint16_t height;
    uint8_t im_fmt;
    uint8_t im_siz;
} Sprite;

typedef enum {
    LINKS_POCKET,
    QUEEN_GOHMA,
    KING_DODONGO,
    BARINADE,
    PHANTOM_GANON,
    VOLVAGIA,
    MORPHA,
    BONGO_BONGO,
    TWINROVA,
    GANON,
    GIFT_FROM_SAGES,
    SONG_FROM_IMPA,
    SONG_FROM_MALON,
    SONG_FROM_SARIA,
    SONG_FROM_ROYAL_FAMILYS_TOMB,
    SONG_FROM_OCARINA_OF_TIME,
    SONG_FROM_WINDMILL,
    SHEIK_IN_FOREST,
    SHEIK_IN_CRATER,
    SHEIK_IN_ICE_CAVERN,
    SHEIK_AT_COLOSSUS,
    SHEIK_IN_KAKARIKO,
    SHEIK_AT_TEMPLE,
    KF_MIDOS_TOP_LEFT_CHEST,
    KF_MIDOS_TOP_RIGHT_CHEST,
    KF_MIDOS_BOTTOM_LEFT_CHEST,
    KF_MIDOS_BOTTOM_RIGHT_CHEST,
    KF_KOKIRI_SWORD_CHEST,
    KF_STORMS_GROTTO_CHEST,
    KF_LINKS_HOUSE_COW,
    KF_GS_KNOW_IT_ALL_HOUSE,
    KF_GS_BEAN_PATCH,
    KF_GS_HOUSE_OF_TWINS,
    KF_SHOP_ITEM_1,
    KF_SHOP_ITEM_2,
    KF_SHOP_ITEM_3,
    KF_SHOP_ITEM_4,
    KF_SHOP_ITEM_5,
    KF_SHOP_ITEM_6,
    KF_SHOP_ITEM_7,
    KF_SHOP_ITEM_8,
    LW_GIFT_FROM_SARIA,
    LW_OCARINA_MEMORY_GAME,
    LW_TARGET_IN_WOODS,
    LW_NEAR_SHORTCUTS_GROTTO_CHEST,
    DEKU_THEATER_SKULL_MASK,
    DEKU_THEATER_MASK_OF_TRUTH,
    LW_SKULL_KID,
    LW_DEKU_SCRUB_NEAR_BRIDGE,
    LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT,
    LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT,
    LW_DEKU_SCRUB_GROTTO_FRONT,
    LW_DEKU_SCRUB_GROTTO_REAR,
    LW_GS_BEAN_PATCH_NEAR_BRIDGE,
    LW_GS_BEAN_PATCH_NEAR_THEATER,
    LW_GS_ABOVE_THEATER,
    SFM_WOLFOS_GROTTO_CHEST,
    SFM_DEKU_SCRUB_GROTTO_FRONT,
    SFM_DEKU_SCRUB_GROTTO_REAR,
    SFM_GS,
    HF_OCARINA_OF_TIME_ITEM,
    HF_NEAR_MARKET_GROTTO_CHEST,
    HF_TEKTITE_GROTTO_FREESTANDING_POH,
    HF_SOUTHEAST_GROTTO_CHEST,
    HF_OPEN_GROTTO_CHEST,
    HF_DEKU_SCRUB_GROTTO,
    HF_COW_GROTTO_COW,
    HF_GS_COW_GROTTO,
    HF_GS_NEAR_KAK_GROTTO,
    MARKET_SHOOTING_GALLERY_REWARD,
    MARKET_BOMBCHU_BOWLING_FIRST_PRIZE,
    MARKET_BOMBCHU_BOWLING_SECOND_PRIZE,
    MARKET_BOMBCHU_BOWLING_BOMBCHUS,
    MARKET_LOST_DOG,
    MARKET_TREASURE_CHEST_GAME_REWARD,
    MARKET_10_BIG_POES,
    MARKET_GS_GUARD_HOUSE,
    MARKET_BAZAAR_ITEM_1,
    MARKET_BAZAAR_ITEM_2,
    MARKET_BAZAAR_ITEM_3,
    MARKET_BAZAAR_ITEM_4,
    MARKET_BAZAAR_ITEM_5,
    MARKET_BAZAAR_ITEM_6,
    MARKET_BAZAAR_ITEM_7,
    MARKET_BAZAAR_ITEM_8,
    MARKET_POTION_SHOP_ITEM_1,
    MARKET_POTION_SHOP_ITEM_2,
    MARKET_POTION_SHOP_ITEM_3,
    MARKET_POTION_SHOP_ITEM_4,
    MARKET_POTION_SHOP_ITEM_5,
    MARKET_POTION_SHOP_ITEM_6,
    MARKET_POTION_SHOP_ITEM_7,
    MARKET_POTION_SHOP_ITEM_8,
    MARKET_BOMBCHU_SHOP_ITEM_1,
    MARKET_BOMBCHU_SHOP_ITEM_2,
    MARKET_BOMBCHU_SHOP_ITEM_3,
    MARKET_BOMBCHU_SHOP_ITEM_4,
    MARKET_BOMBCHU_SHOP_ITEM_5,
    MARKET_BOMBCHU_SHOP_ITEM_6,
    MARKET_BOMBCHU_SHOP_ITEM_7,
    MARKET_BOMBCHU_SHOP_ITEM_8,
    TOT_LIGHT_ARROWS_CUTSCENE,
    HC_MALON_EGG,
    HC_ZELDAS_LETTER,
    HC_GREAT_FAIRY_REWARD,
    HC_GS_TREE,
    HC_GS_STORMS_GROTTO,
    LLR_TALONS_CHICKENS,
    LLR_FREESTANDING_POH,
    LLR_DEKU_SCRUB_GROTTO_LEFT,
    LLR_DEKU_SCRUB_GROTTO_CENTER,
    LLR_DEKU_SCRUB_GROTTO_RIGHT,
    LLR_STABLES_LEFT_COW,
    LLR_STABLES_RIGHT_COW,
    LLR_TOWER_LEFT_COW,
    LLR_TOWER_RIGHT_COW,
    LLR_GS_HOUSE_WINDOW,
    LLR_GS_TREE,
    LLR_GS_RAIN_SHED,
    LLR_GS_BACK_WALL,
    KAK_ANJU_AS_CHILD,
    KAK_ANJU_AS_ADULT,
    KAK_IMPAS_HOUSE_FREESTANDING_POH,
    KAK_WINDMILL_FREESTANDING_POH,
    KAK_MAN_ON_ROOF,
    KAK_OPEN_GROTTO_CHEST,
    KAK_REDEAD_GROTTO_CHEST,
    KAK_SHOOTING_GALLERY_REWARD,
    KAK_10_GOLD_SKULLTULA_REWARD,
    KAK_20_GOLD_SKULLTULA_REWARD,
    KAK_30_GOLD_SKULLTULA_REWARD,
    KAK_40_GOLD_SKULLTULA_REWARD,
    KAK_50_GOLD_SKULLTULA_REWARD,
    KAK_IMPAS_HOUSE_COW,
    KAK_GS_TREE,
    KAK_GS_GUARDS_HOUSE,
    KAK_GS_WATCHTOWER,
    KAK_GS_SKULLTULA_HOUSE,
    KAK_GS_HOUSE_UNDER_CONSTRUCTION,
    KAK_GS_ABOVE_IMPAS_HOUSE,
    KAK_BAZAAR_ITEM_1,
    KAK_BAZAAR_ITEM_2,
    KAK_BAZAAR_ITEM_3,
    KAK_BAZAAR_ITEM_4,
    KAK_BAZAAR_ITEM_5,
    KAK_BAZAAR_ITEM_6,
    KAK_BAZAAR_ITEM_7,
    KAK_BAZAAR_ITEM_8,
    KAK_POTION_SHOP_ITEM_1,
    KAK_POTION_SHOP_ITEM_2,
    KAK_POTION_SHOP_ITEM_3,
    KAK_POTION_SHOP_ITEM_4,
    KAK_POTION_SHOP_ITEM_5,
    KAK_POTION_SHOP_ITEM_6,
    KAK_POTION_SHOP_ITEM_7,
    KAK_POTION_SHOP_ITEM_8,
    GRAVEYARD_SHIELD_GRAVE_CHEST,
    GRAVEYARD_HEART_PIECE_GRAVE_CHEST,
    GRAVEYARD_ROYAL_FAMILYS_TOMB_CHEST,
    GRAVEYARD_FREESTANDING_POH,
    GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR,
    GRAVEYARD_HOOKSHOT_CHEST,
    GRAVEYARD_DAMPE_RACE_FREESTANDING_POH,
    GRAVEYARD_GS_BEAN_PATCH,
    GRAVEYARD_GS_WALL,
    DMT_FREESTANDING_POH,
    DMT_CHEST,
    DMT_STORMS_GROTTO_CHEST,
    DMT_GREAT_FAIRY_REWARD,
    DMT_BIGGORON,
    DMT_COW_GROTTO_COW,
    DMT_GS_NEAR_KAK,
    DMT_GS_BEAN_PATCH,
    DMT_GS_ABOVE_DODONGOS_CAVERN,
    DMT_GS_FALLING_ROCKS_PATH,
    GC_DARUNIAS_JOY,
    GC_POT_FREESTANDING_POH,
    GC_ROLLING_GORON_AS_CHILD,
    GC_ROLLING_GORON_AS_ADULT,
    GC_MEDIGORON,
    GC_MAZE_LEFT_CHEST,
    GC_MAZE_RIGHT_CHEST,
    GC_MAZE_CENTER_CHEST,
    GC_DEKU_SCRUB_GROTTO_LEFT,
    GC_DEKU_SCRUB_GROTTO_CENTER,
    GC_DEKU_SCRUB_GROTTO_RIGHT,
    GC_GS_CENTER_PLATFORM,
    GC_GS_BOULDER_MAZE,
    GC_SHOP_ITEM_1,
    GC_SHOP_ITEM_2,
    GC_SHOP_ITEM_3,
    GC_SHOP_ITEM_4,
    GC_SHOP_ITEM_5,
    GC_SHOP_ITEM_6,
    GC_SHOP_ITEM_7,
    GC_SHOP_ITEM_8,
    DMC_VOLCANO_FREESTANDING_POH,
    DMC_WALL_FREESTANDING_POH,
    DMC_UPPER_GROTTO_CHEST,
    DMC_GREAT_FAIRY_REWARD,
    DMC_DEKU_SCRUB,
    DMC_DEKU_SCRUB_GROTTO_LEFT,
    DMC_DEKU_SCRUB_GROTTO_CENTER,
    DMC_DEKU_SCRUB_GROTTO_RIGHT,
    DMC_GS_CRATE,
    DMC_GS_BEAN_PATCH,
    ZR_MAGIC_BEAN_SALESMAN,
    ZR_OPEN_GROTTO_CHEST,
    ZR_FROGS_ZELDAS_LULLABY,
    ZR_FROGS_EPONAS_SONG,
    ZR_FROGS_SARIAS_SONG,
    ZR_FROGS_SUNS_SONG,
    ZR_FROGS_SONG_OF_TIME,
    ZR_FROGS_IN_THE_RAIN,
    ZR_FROGS_OCARINA_GAME,
    ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH,
    ZR_NEAR_DOMAIN_FREESTANDING_POH,
    ZR_DEKU_SCRUB_GROTTO_FRONT,
    ZR_DEKU_SCRUB_GROTTO_REAR,
    ZR_GS_TREE,
    ZR_GS_LADDER,
    ZR_GS_NEAR_RAISED_GROTTOS,
    ZR_GS_ABOVE_BRIDGE,
    ZD_DIVING_MINIGAME,
    ZD_CHEST,
    ZD_KING_ZORA_THAWED,
    ZD_GS_FROZEN_WATERFALL,
    ZD_SHOP_ITEM_1,
    ZD_SHOP_ITEM_2,
    ZD_SHOP_ITEM_3,
    ZD_SHOP_ITEM_4,
    ZD_SHOP_ITEM_5,
    ZD_SHOP_ITEM_6,
    ZD_SHOP_ITEM_7,
    ZD_SHOP_ITEM_8,
    ZF_GREAT_FAIRY_REWARD,
    ZF_ICEBERG_FREESTANDING_POH,
    ZF_BOTTOM_FREESTANDING_POH,
    ZF_GS_ABOVE_THE_LOG,
    ZF_GS_TREE,
    ZF_GS_HIDDEN_CAVE,
    LH_UNDERWATER_ITEM,
    LH_CHILD_FISHING,
    LH_ADULT_FISHING,
    LH_LAB_DIVE,
    LH_FREESTANDING_POH,
    LH_SUN,
    LH_DEKU_SCRUB_GROTTO_LEFT,
    LH_DEKU_SCRUB_GROTTO_CENTER,
    LH_DEKU_SCRUB_GROTTO_RIGHT,
    LH_GS_BEAN_PATCH,
    LH_GS_LAB_WALL,
    LH_GS_SMALL_ISLAND,
    LH_GS_LAB_CRATE,
    LH_GS_TREE,
    GV_CRATE_FREESTANDING_POH,
    GV_WATERFALL_FREESTANDING_POH,
    GV_CHEST,
    GV_DEKU_SCRUB_GROTTO_FRONT,
    GV_DEKU_SCRUB_GROTTO_REAR,
    GV_COW,
    GV_GS_SMALL_BRIDGE,
    GV_GS_BEAN_PATCH,
    GV_GS_BEHIND_TENT,
    GV_GS_PILLAR,
    GF_CHEST,
    GF_HBA_1000_POINTS,
    GF_HBA_1500_POINTS,
    GF_GS_TOP_FLOOR,
    GF_GS_ARCHERY_RANGE,
    HIDEOUT_JAIL_GUARD_1_TORCH,
    HIDEOUT_JAIL_GUARD_2_TORCHES,
    HIDEOUT_JAIL_GUARD_3_TORCHES,
    HIDEOUT_JAIL_GUARD_4_TORCHES,
    HIDEOUT_GERUDO_MEMBERSHIP_CARD,
    WASTELAND_BOMBCHU_SALESMAN,
    WASTELAND_CHEST,
    WASTELAND_GS,
    COLOSSUS_GREAT_FAIRY_REWARD,
    COLOSSUS_FREESTANDING_POH,
    COLOSSUS_DEKU_SCRUB_GROTTO_FRONT,
    COLOSSUS_DEKU_SCRUB_GROTTO_REAR,
    COLOSSUS_GS_BEAN_PATCH,
    COLOSSUS_GS_TREE,
    COLOSSUS_GS_HILL,
    OGC_GREAT_FAIRY_REWARD,
    OGC_GS,
    DEKU_TREE_MAP_CHEST,
    DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST,
    DEKU_TREE_SLINGSHOT_CHEST,
    DEKU_TREE_COMPASS_CHEST,
    DEKU_TREE_COMPASS_ROOM_SIDE_CHEST,
    DEKU_TREE_BASEMENT_CHEST,
    DEKU_TREE_GS_COMPASS_ROOM,
    DEKU_TREE_GS_BASEMENT_VINES,
    DEKU_TREE_GS_BASEMENT_GATE,
    DEKU_TREE_GS_BASEMENT_BACK_ROOM,
    DEKU_TREE_MQ_MAP_CHEST,
    DEKU_TREE_MQ_SLINGSHOT_CHEST,
    DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST,
    DEKU_TREE_MQ_COMPASS_CHEST,
    DEKU_TREE_MQ_BASEMENT_CHEST,
    DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST,
    DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST,
    DEKU_TREE_MQ_DEKU_SCRUB,
    DEKU_TREE_MQ_GS_LOBBY,
    DEKU_TREE_MQ_GS_COMPASS_ROOM,
    DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM,
    DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM,
    DEKU_TREE_QUEEN_GOHMA_HEART,
    DODONGOS_CAVERN_MAP_CHEST,
    DODONGOS_CAVERN_COMPASS_CHEST,
    DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST,
    DODONGOS_CAVERN_BOMB_BAG_CHEST,
    DODONGOS_CAVERN_END_OF_BRIDGE_CHEST,
    DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS,
    DODONGOS_CAVERN_DEKU_SCRUB_LOBBY,
    DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT,
    DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT,
    DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS,
    DODONGOS_CAVERN_GS_SCARECROW,
    DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS,
    DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS,
    DODONGOS_CAVERN_GS_BACK_ROOM,
    DODONGOS_CAVERN_MQ_MAP_CHEST,
    DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST,
    DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST,
    DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST,
    DODONGOS_CAVERN_MQ_COMPASS_CHEST,
    DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST,
    DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT,
    DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR,
    DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS,
    DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE,
    DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM,
    DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM,
    DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM,
    DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM,
    DODONGOS_CAVERN_MQ_GS_BACK_AREA,
    DODONGOS_CAVERN_BOSS_ROOM_CHEST,
    DODONGOS_CAVERN_KING_DODONGO_HEART,
    JABU_JABUS_BELLY_BOOMERANG_CHEST,
    JABU_JABUS_BELLY_MAP_CHEST,
    JABU_JABUS_BELLY_COMPASS_CHEST,
    JABU_JABUS_BELLY_DEKU_SCRUB,
    JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM,
    JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER,
    JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER,
    JABU_JABUS_BELLY_GS_NEAR_BOSS,
    JABU_JABUS_BELLY_MQ_MAP_CHEST,
    JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST,
    JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST,
    JABU_JABUS_BELLY_MQ_COMPASS_CHEST,
    JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST,
    JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST,
    JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST,
    JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST,
    JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST,
    JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST,
    JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST,
    JABU_JABUS_BELLY_MQ_COW,
    JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM,
    JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM,
    JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM,
    JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS,
    JABU_JABUS_BELLY_BARINADE_HEART,
    BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST,
    BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST,
    BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST,
    BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST,
    BOTTOM_OF_THE_WELL_FREESTANDING_KEY,
    BOTTOM_OF_THE_WELL_COMPASS_CHEST,
    BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST,
    BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST,
    BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST,
    BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST,
    BOTTOM_OF_THE_WELL_MAP_CHEST,
    BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST,
    BOTTOM_OF_THE_WELL_INVISIBLE_CHEST,
    BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST,
    BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM,
    BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM,
    BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE,
    BOTTOM_OF_THE_WELL_MQ_MAP_CHEST,
    BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY,
    BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST,
    BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY,
    BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST,
    BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM,
    BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM,
    BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT,
    FOREST_TEMPLE_FIRST_ROOM_CHEST,
    FOREST_TEMPLE_FIRST_STALFOS_CHEST,
    FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST,
    FOREST_TEMPLE_MAP_CHEST,
    FOREST_TEMPLE_WELL_CHEST,
    FOREST_TEMPLE_EYE_SWITCH_CHEST,
    FOREST_TEMPLE_BOSS_KEY_CHEST,
    FOREST_TEMPLE_FLOORMASTER_CHEST,
    FOREST_TEMPLE_RED_POE_CHEST,
    FOREST_TEMPLE_BOW_CHEST,
    FOREST_TEMPLE_BLUE_POE_CHEST,
    FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST,
    FOREST_TEMPLE_BASEMENT_CHEST,
    FOREST_TEMPLE_GS_FIRST_ROOM,
    FOREST_TEMPLE_GS_LOBBY,
    FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD,
    FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD,
    FOREST_TEMPLE_GS_BASEMENT,
    FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST,
    FOREST_TEMPLE_MQ_WOLFOS_CHEST,
    FOREST_TEMPLE_MQ_WELL_CHEST,
    FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST,
    FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST,
    FOREST_TEMPLE_MQ_BOSS_KEY_CHEST,
    FOREST_TEMPLE_MQ_REDEAD_CHEST,
    FOREST_TEMPLE_MQ_MAP_CHEST,
    FOREST_TEMPLE_MQ_BOW_CHEST,
    FOREST_TEMPLE_MQ_COMPASS_CHEST,
    FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST,
    FOREST_TEMPLE_MQ_BASEMENT_CHEST,
    FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY,
    FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD,
    FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD,
    FOREST_TEMPLE_MQ_GS_WELL,
    FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM,
    FOREST_TEMPLE_PHANTOM_GANON_HEART,
    FIRE_TEMPLE_NEAR_BOSS_CHEST,
    FIRE_TEMPLE_FLARE_DANCER_CHEST,
    FIRE_TEMPLE_BOSS_KEY_CHEST,
    FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST,
    FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST,
    FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST,
    FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST,
    FIRE_TEMPLE_MAP_CHEST,
    FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST,
    FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST,
    FIRE_TEMPLE_SCARECROW_CHEST,
    FIRE_TEMPLE_COMPASS_CHEST,
    FIRE_TEMPLE_MEGATON_HAMMER_CHEST,
    FIRE_TEMPLE_HIGHEST_GORON_CHEST,
    FIRE_TEMPLE_GS_BOSS_KEY_LOOP,
    FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM,
    FIRE_TEMPLE_GS_BOULDER_MAZE,
    FIRE_TEMPLE_GS_SCARECROW_CLIMB,
    FIRE_TEMPLE_GS_SCARECROW_TOP,
    FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST,
    FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST,
    FIRE_TEMPLE_MQ_MAP_CHEST,
    FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST,
    FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST,
    FIRE_TEMPLE_MQ_BOSS_KEY_CHEST,
    FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST,
    FIRE_TEMPLE_MQ_COMPASS_CHEST,
    FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST,
    FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST,
    FIRE_TEMPLE_MQ_FREESTANDING_KEY,
    FIRE_TEMPLE_MQ_CHEST_ON_FIRE,
    FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR,
    FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE,
    FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER,
    FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM,
    FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_WALL_MAZE,
    FIRE_TEMPLE_VOLVAGIA_HEART,
    WATER_TEMPLE_COMPASS_CHEST,
    WATER_TEMPLE_MAP_CHEST,
    WATER_TEMPLE_CRACKED_WALL_CHEST,
    WATER_TEMPLE_TORCHES_CHEST,
    WATER_TEMPLE_BOSS_KEY_CHEST,
    WATER_TEMPLE_CENTRAL_PILLAR_CHEST,
    WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST,
    WATER_TEMPLE_LONGSHOT_CHEST,
    WATER_TEMPLE_RIVER_CHEST,
    WATER_TEMPLE_DRAGON_CHEST,
    WATER_TEMPLE_GS_BEHIND_GATE,
    WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST,
    WATER_TEMPLE_GS_CENTRAL_PILLAR,
    WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM,
    WATER_TEMPLE_GS_RIVER,
    WATER_TEMPLE_MQ_LONGSHOT_CHEST,
    WATER_TEMPLE_MQ_MAP_CHEST,
    WATER_TEMPLE_MQ_COMPASS_CHEST,
    WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST,
    WATER_TEMPLE_MQ_BOSS_KEY_CHEST,
    WATER_TEMPLE_MQ_FREESTANDING_KEY,
    WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY,
    WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH,
    WATER_TEMPLE_MQ_GS_RIVER,
    WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA,
    WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH,
    WATER_TEMPLE_MORPHA_HEART,
    SHADOW_TEMPLE_MAP_CHEST,
    SHADOW_TEMPLE_HOVER_BOOTS_CHEST,
    SHADOW_TEMPLE_COMPASS_CHEST,
    SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST,
    SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST,
    SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST,
    SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST,
    SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST,
    SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST,
    SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST,
    SHADOW_TEMPLE_FREESTANDING_KEY,
    SHADOW_TEMPLE_WIND_HINT_CHEST,
    SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST,
    SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST,
    SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST,
    SHADOW_TEMPLE_BOSS_KEY_CHEST,
    SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST,
    SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM,
    SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM,
    SHADOW_TEMPLE_GS_SINGLE_GIANT_POT,
    SHADOW_TEMPLE_GS_NEAR_SHIP,
    SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT,
    SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST,
    SHADOW_TEMPLE_MQ_MAP_CHEST,
    SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST,
    SHADOW_TEMPLE_MQ_COMPASS_CHEST,
    SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST,
    SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST,
    SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST,
    SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST,
    SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST,
    SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST,
    SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST,
    SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST,
    SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST,
    SHADOW_TEMPLE_MQ_WIND_HINT_CHEST,
    SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST,
    SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST,
    SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST,
    SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST,
    SHADOW_TEMPLE_MQ_FREESTANDING_KEY,
    SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST,
    SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM,
    SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM,
    SHADOW_TEMPLE_MQ_GS_AFTER_WIND,
    SHADOW_TEMPLE_MQ_GS_AFTER_SHIP,
    SHADOW_TEMPLE_MQ_GS_NEAR_BOSS,
    SHADOW_TEMPLE_BONGO_BONGO_HEART,
    SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST,
    SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST,
    SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST,
    SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST,
    SPIRIT_TEMPLE_MAP_CHEST,
    SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST,
    SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST,
    SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST,
    SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST,
    SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST,
    SPIRIT_TEMPLE_MQ_MAP_CHEST,
    SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST,
    SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST,
    SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST,
    SPIRIT_TEMPLE_MQ_COMPASS_CHEST,
    SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST,
    SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST,
    SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST,
    SPIRIT_TEMPLE_COMPASS_CHEST,
    SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST,
    SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST,
    SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST,
    SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST,
    SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST,
    SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST,
    SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST,
    SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST,
    SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST,
    SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST,
    SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST,
    SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST,
    SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST,
    SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST,
    SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST,
    SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST,
    SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST,
    SPIRIT_TEMPLE_BOSS_KEY_CHEST,
    SPIRIT_TEMPLE_TOPMOST_CHEST,
    SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST,
    SPIRIT_TEMPLE_GS_METAL_FENCE,
    SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM,
    SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM,
    SPIRIT_TEMPLE_GS_LOBBY,
    SPIRIT_TEMPLE_GS_BOULDER_ROOM,
    SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM,
    SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM,
    SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM,
    SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST,
    SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH,
    SPIRIT_TEMPLE_TWINROVA_HEART,
    ICE_CAVERN_MAP_CHEST,
    ICE_CAVERN_COMPASS_CHEST,
    ICE_CAVERN_FREESTANDING_POH,
    ICE_CAVERN_IRON_BOOTS_CHEST,
    ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM,
    ICE_CAVERN_GS_HEART_PIECE_ROOM,
    ICE_CAVERN_GS_PUSH_BLOCK_ROOM,
    ICE_CAVERN_MQ_MAP_CHEST,
    ICE_CAVERN_MQ_COMPASS_CHEST,
    ICE_CAVERN_MQ_FREESTANDING_POH,
    ICE_CAVERN_MQ_IRON_BOOTS_CHEST,
    ICE_CAVERN_MQ_GS_RED_ICE,
    ICE_CAVERN_MQ_GS_ICE_BLOCK,
    ICE_CAVERN_MQ_GS_SCARECROW,
    GERUDO_TRAINING_GROUND_LOBBY_LEFT_CHEST,
    GERUDO_TRAINING_GROUND_LOBBY_RIGHT_CHEST,
    GERUDO_TRAINING_GROUND_STALFOS_CHEST,
    GERUDO_TRAINING_GROUND_BEFORE_HEAVY_BLOCK_CHEST,
    GERUDO_TRAINING_GROUND_HEAVY_BLOCK_FIRST_CHEST,
    GERUDO_TRAINING_GROUND_HEAVY_BLOCK_SECOND_CHEST,
    GERUDO_TRAINING_GROUND_HEAVY_BLOCK_THIRD_CHEST,
    GERUDO_TRAINING_GROUND_HEAVY_BLOCK_FOURTH_CHEST,
    GERUDO_TRAINING_GROUND_EYE_STATUE_CHEST,
    GERUDO_TRAINING_GROUND_NEAR_SCARECROW_CHEST,
    GERUDO_TRAINING_GROUND_HAMMER_ROOM_CLEAR_CHEST,
    GERUDO_TRAINING_GROUND_HAMMER_ROOM_SWITCH_CHEST,
    GERUDO_TRAINING_GROUND_FREESTANDING_KEY,
    GERUDO_TRAINING_GROUND_MAZE_RIGHT_CENTRAL_CHEST,
    GERUDO_TRAINING_GROUND_MAZE_RIGHT_SIDE_CHEST,
    GERUDO_TRAINING_GROUND_UNDERWATER_SILVER_RUPEE_CHEST,
    GERUDO_TRAINING_GROUND_BEAMOS_CHEST,
    GERUDO_TRAINING_GROUND_HIDDEN_CEILING_CHEST,
    GERUDO_TRAINING_GROUND_MAZE_PATH_FIRST_CHEST,
    GERUDO_TRAINING_GROUND_MAZE_PATH_SECOND_CHEST,
    GERUDO_TRAINING_GROUND_MAZE_PATH_THIRD_CHEST,
    GERUDO_TRAINING_GROUND_MAZE_PATH_FINAL_CHEST,
    GERUDO_TRAINING_GROUND_MQ_LOBBY_LEFT_CHEST,
    GERUDO_TRAINING_GROUND_MQ_LOBBY_RIGHT_CHEST,
    GERUDO_TRAINING_GROUND_MQ_FIRST_IRON_KNUCKLE_CHEST,
    GERUDO_TRAINING_GROUND_MQ_BEFORE_HEAVY_BLOCK_CHEST,
    GERUDO_TRAINING_GROUND_MQ_HEAVY_BLOCK_CHEST,
    GERUDO_TRAINING_GROUND_MQ_EYE_STATUE_CHEST,
    GERUDO_TRAINING_GROUND_MQ_ICE_ARROWS_CHEST,
    GERUDO_TRAINING_GROUND_MQ_SECOND_IRON_KNUCKLE_CHEST,
    GERUDO_TRAINING_GROUND_MQ_FLAME_CIRCLE_CHEST,
    GERUDO_TRAINING_GROUND_MQ_MAZE_RIGHT_CENTRAL_CHEST,
    GERUDO_TRAINING_GROUND_MQ_MAZE_RIGHT_SIDE_CHEST,
    GERUDO_TRAINING_GROUND_MQ_UNDERWATER_SILVER_RUPEE_CHEST,
    GERUDO_TRAINING_GROUND_MQ_DINOLFOS_CHEST,
    GERUDO_TRAINING_GROUND_MQ_HIDDEN_CEILING_CHEST,
    GERUDO_TRAINING_GROUND_MQ_MAZE_PATH_FIRST_CHEST,
    GERUDO_TRAINING_GROUND_MQ_MAZE_PATH_THIRD_CHEST,
    GERUDO_TRAINING_GROUND_MQ_MAZE_PATH_SECOND_CHEST,
    GANONS_CASTLE_FOREST_TRIAL_CHEST,
    GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST,
    GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST,
    GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST,
    GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST,
    GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST,
    GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST,
    GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST,
    GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST,
    GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST,
    GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST,
    GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST,
    GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST,
    GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST,
    GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST,
    GANONS_CASTLE_DEKU_SCRUB_LEFT,
    GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT,
    GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT,
    GANONS_CASTLE_DEKU_SCRUB_RIGHT,
    GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY,
    GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST,
    GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST,
    GANONS_CASTLE_MQ_WATER_TRIAL_CHEST,
    GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST,
    GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST,
    GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST,
    GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST,
    GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST,
    GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST,
    GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST,
    GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST,
    GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST,
    GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT,
    GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT,
    GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER,
    GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT,
    GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT,
    GANONS_TOWER_BOSS_KEY_CHEST,
    PIERRE,
    DELIVER_RUTOS_LETTER,
    MASTER_SWORD_PEDESTAL,
    UNKNOWN_CHECK
} RandomizerCheck;

// based on https://github.com/TestRunnerSRL/OoT-Randomizer/blob/e337d7f603b91a6bacb618fb32cc7fd70ed9ffca/ItemList.py
typedef enum {
    UNKNOWN_GET = 0,
    BOMBS_5,
    DEKU_NUTS_5,
    BOMBCHUS_10,
    BOOMERANG,
    DEKU_STICK_1,
    LENS_OF_TRUTH,
    MEGATON_HAMMER,
    COJIRO,
    BOTTLE,
    BOTTLE_WITH_MILK,
    RUTOS_LETTER,
    DELIVER_LETTER,
    SELL_BIG_POE,
    MAGIC_BEAN,
    SKULL_MASK,
    SPOOKY_MASK,
    KEATON_MASK,
    BUNNY_HOOD,
    MASK_OF_TRUTH,
    POCKET_EGG,
    POCKET_CUCCO,
    ODD_MUSHROOM,
    ODD_POTION,
    POACHERS_SAW,
    BROKEN_SWORD,
    PRESCRIPTION,
    EYEBALL_FROG,
    EYEDROPS,
    CLAIM_CHECK,
    KOKIRI_SWORD,
    GIANTS_KNIFE,
    DEKU_SHIELD,
    HYLIAN_SHIELD,
    MIRROR_SHIELD,
    GORON_TUNIC,
    ZORA_TUNIC,
    IRON_BOOTS,
    HOVER_BOOTS,
    STONE_OF_AGONY,
    GERUDO_MEMBERSHIP_CARD,
    HEART_CONTAINER,
    PIECE_OF_HEART,
    BOSS_KEY,
    COMPASS,
    MAP,
    SMALL_KEY,
    WEIRD_EGG,
    RECOVERY_HEART,
    ARROWS_5,
    ARROWS_10,
    ARROWS_30,
    RUPEE_1,
    RUPEES_5,
    RUPEES_20,
    MILK,
    GORON_MASK,
    ZORA_MASK,
    GERUDO_MASK,
    RUPEES_50,
    RUPEES_200,
    BIGGORON_SWORD,
    FIRE_ARROWS,
    ICE_ARROWS,
    LIGHT_ARROWS,
    GOLD_SKULLTULA_TOKEN,
    DINS_FIRE,
    NAYRUS_LOVE,
    FARORES_WIND,
    DEKU_NUTS_10,
    BOMBS_10,
    BOMBS_20,
    DEKU_SEEDS_30,
    BOMBCHUS_5,
    BOMBCHUS_20,
    RUPEE_TREASURE_CHEST_GAME,
    PIECE_OF_HEART_TREASURE_CHEST_GAME,
    ICE_TRAP,
    PROGRESSIVE_HOOKSHOT,
    PROGRESSIVE_STRENGTH_UPGRADE,
    BOMB_BAG,
    BOW,
    SLINGSHOT,
    PROGRESSIVE_WALLET,
    PROGRESSIVE_SCALE,
    DEKU_NUT_CAPACITY,
    DEKU_STICK_CAPACITY,
    BOMBCHUS,
    MAGIC_METER,
    OCARINA,
    BOTTLE_WITH_RED_POTION,
    BOTTLE_WITH_GREEN_POTION,
    BOTTLE_WITH_BLUE_POTION,
    BOTTLE_WITH_FAIRY,
    BOTTLE_WITH_FISH,
    BOTTLE_WITH_BLUE_FIRE,
    BOTTLE_WITH_BUGS,
    BOTTLE_WITH_BIG_POE,
    BOTTLE_WITH_POE,
    BOSS_KEY_FOREST_TEMPLE,
    BOSS_KEY_FIRE_TEMPLE,
    BOSS_KEY_WATER_TEMPLE,
    BOSS_KEY_SPIRIT_TEMPLE,
    BOSS_KEY_SHADOW_TEMPLE,
    BOSS_KEY_GANONS_CASTLE,
    COMPASS_DEKU_TREE,
    COMPASS_DODONGOS_CAVERN,
    COMPASS_JABU_JABUS_BELLY,
    COMPASS_FOREST_TEMPLE,
    COMPASS_FIRE_TEMPLE,
    COMPASS_WATER_TEMPLE,
    COMPASS_SPIRIT_TEMPLE,
    COMPASS_SHADOW_TEMPLE,
    COMPASS_BOTTOM_OF_THE_WELL,
    COMPASS_ICE_CAVERN,
    MAP_DEKU_TREE,
    MAP_DODONGOS_CAVERN,
    MAP_JABU_JABUS_BELLY,
    MAP_FOREST_TEMPLE,
    MAP_FIRE_TEMPLE,
    MAP_WATER_TEMPLE,
    MAP_SPIRIT_TEMPLE,
    MAP_SHADOW_TEMPLE,
    MAP_BOTTOM_OF_THE_WELL,
    MAP_ICE_CAVERN,
    SMALL_KEY_FOREST_TEMPLE,
    SMALL_KEY_FIRE_TEMPLE,
    SMALL_KEY_WATER_TEMPLE,
    SMALL_KEY_SPIRIT_TEMPLE,
    SMALL_KEY_SHADOW_TEMPLE,
    SMALL_KEY_BOTTOM_OF_THE_WELL,
    SMALL_KEY_GERUDO_TRAINING_GROUND,
    SMALL_KEY_THIEVES_HIDEOUT,
    SMALL_KEY_GANONS_CASTLE,
    DOUBLE_DEFENSE,
    MAGIC_BEAN_PACK,
    TRIFORCE_PIECE,
    ZELDAS_LETTER,
    TIME_TRAVEL,
    SCARECROW_SONG,
    TRIFORCE,
    SMALL_KEY_RING_FOREST_TEMPLE,
    SMALL_KEY_RING_FIRE_TEMPLE,
    SMALL_KEY_RING_WATER_TEMPLE,
    SMALL_KEY_RING_SPIRIT_TEMPLE,
    SMALL_KEY_RING_SHADOW_TEMPLE,
    SMALL_KEY_RING_BOTTOM_OF_THE_WELL,
    SMALL_KEY_RING_GERUDO_TRAINING_GROUND,
    SMALL_KEY_RING_THIEVES_HIDEOUT,
    SMALL_KEY_RING_GANONS_CASTLE,
    WATER_TEMPLE_CLEAR,
    FOREST_TRIAL_CLEAR,
    FIRE_TRIAL_CLEAR,
    WATER_TRIAL_CLEAR,
    SHADOW_TRIAL_CLEAR,
    SPIRIT_TRIAL_CLEAR,
    LIGHT_TRIAL_CLEAR,
    DEKU_STICK_DROP,
    DEKU_NUT_DROP,
    BLUE_FIRE,
    FAIRY,
    FISH,
    BUGS,
    BIG_POE,
    BOMBCHU_DROP,
    ARROWS_CONSUMABLE_REFILL,
    BOMBS_CONSUMABLE_REFILL,
    DEKU_SEEDS_CONSUMABLE_REFILL,
    DEKU_STICKS_CONSUMABLE_REFILL,
    DEKU_NUTS_CONSUMABLE_REFILL,
    RUPEES_CONSUMABLE_REFILL,
    MINUET_OF_FOREST,
    BOLERO_OF_FIRE,
    SERENADE_OF_WATER,
    REQUIEM_OF_SPIRIT,
    NOCTURNE_OF_SHADOW,
    PRELUDE_OF_LIGHT,
    ZELDAS_LULLABY,
    EPONAS_SONG,
    SARIAS_SONG,
    SUNS_SONG,
    SONG_OF_TIME,
    SONG_OF_STORMS,
    BUY_DEKU_NUT_5,
    BUY_ARROWS_30,
    BUY_ARROWS_50,
    BUY_BOMBS_5_FOR_25_RUPEES,
    BUY_DEKU_NUT_10,
    BUY_DEKU_STICK_1,
    BUY_BOMBS_10,
    BUY_FISH,
    BUY_RED_POTION_FOR_30_RUPEES,
    BUY_GREEN_POTION,
    BUY_BLUE_POTION,
    BUY_HYLIAN_SHIELD,
    BUY_DEKU_SHIELD,
    BUY_GORON_TUNIC,
    BUY_ZORA_TUNIC,
    BUY_HEART,
    BUY_BOMBCHU_10,
    BUY_BOMBCHU_20,
    BUY_BOMBCHU_5,
    BUY_DEKU_SEEDS_30,
    SOLD_OUT,
    BUY_BLUE_FIRE,
    BUY_BOTTLE_BUG,
    BUY_POE,
    BUY_FAIRYS_SPIRIT,
    BUY_ARROWS_10,
    BUY_BOMBS_20,
    BUY_BOMBS_30,
    BUY_BOMBS_5_FOR_35_RUPEES,
    BUY_RED_POTION_FOR_40_RUPEES,
    BUY_RED_POTION_FOR_50_RUPEES,
    KOKIRI_EMERALD,
    GORON_RUBY,
    ZORA_SAPPHIRE,
    FOREST_MEDALLION,
    FIRE_MEDALLION,
    WATER_MEDALLION,
    SPIRIT_MEDALLION,
    SHADOW_MEDALLION,
    LIGHT_MEDALLION
} RandomizerGet;
