MODULE := engines/gob

MODULE_OBJS := \
	anifile.o \
	aniobject.o \
	backbuffer.o \
	cheater.o \
	cheater_geisha.o \
	cmpfile.o \
	console.o \
	databases.o \
	dataio.o \
	dbase.o \
	decfile.o \
	draw.o \
	draw_v1.o \
	draw_v2.o \
	draw_v7.o \
	draw_bargon.o \
	draw_fascin.o \
	draw_playtoons.o \
	expression.o \
	game.o \
	global.o \
	gob.o \
	goblin.o \
	goblin_v1.o \
	goblin_v2.o \
	goblin_v3.o \
	goblin_v4.o \
	goblin_v7.o \
	hotspots.o \
	html_parser.o \
	iniconfig.o \
	init.o \
	init_v1.o \
	init_geisha.o \
	init_v2.o \
	init_fascin.o \
	init_v3.o \
	init_v4.o \
	init_v6.o \
	init_v7.o \
	inter.o \
	inter_v1.o \
	inter_geisha.o \
	inter_v2.o \
	inter_adibou1.o \
	inter_bargon.o \
	inter_fascin.o \
	inter_littlered.o \
	inter_inca2.o \
	inter_playtoons.o \
	inter_v3.o \
	inter_v4.o \
	inter_v5.o \
	inter_v6.o \
	inter_v7.o \
	map.o \
	map_v1.o \
	map_v2.o \
	metaengine.o \
	mult.o \
	mult_v1.o \
	mult_v2.o \
	palanim.o \
	resources.o \
	rxyfile.o \
	scenery.o \
	scenery_v1.o \
	scenery_v2.o \
	script.o \
	surface.o \
	totfile.o \
	util.o \
	variables.o \
	video.o \
	video_v1.o \
	video_v2.o \
	video_v6.o \
	videoplayer.o \
	demos/demoplayer.o \
	demos/scnplayer.o \
	demos/batplayer.o \
	image/brc.o \
	pregob/pregob.o \
	pregob/txtfile.o \
	pregob/gctfile.o \
	pregob/seqfile.o \
	pregob/onceupon/onceupon.o \
	pregob/onceupon/abracadabra.o \
	pregob/onceupon/babayaga.o \
	pregob/onceupon/title.o \
	pregob/onceupon/parents.o \
	pregob/onceupon/stork.o \
	pregob/onceupon/chargenchild.o \
	minigames/geisha/evilfish.o \
	minigames/geisha/oko.o \
	minigames/geisha/meter.o \
	minigames/geisha/diving.o \
	minigames/geisha/mouth.o \
	minigames/geisha/submarine.o \
	minigames/geisha/penetration.o \
	save/savefile.o \
	save/savehandler.o \
	save/saveload.o \
	save/saveload_v2.o \
	save/saveload_v3.o \
	save/saveload_v4.o \
	save/saveload_v6.o \
	save/saveload_v7.o \
	save/saveload_adibou1.o \
	save/saveload_geisha.o \
	save/saveload_fascin.o \
	save/saveload_inca2.o \
	save/saveload_playtoons.o \
	save/saveconverter.o \
	save/saveconverter_v2.o \
	save/saveconverter_v3.o \
	save/saveconverter_v4.o \
	sound/sound.o \
	sound/sounddesc.o \
	sound/pcspeaker.o \
	sound/adlib.o \
	sound/musplayer.o \
	sound/adlplayer.o \
	sound/infogrames.o \
	sound/protracker.o \
	sound/soundmixer.o \
	sound/soundblaster.o \
	sound/cdrom.o \
	sound/bgatmosphere.o

# This module can be built as a plugin
ifeq ($(ENABLE_GOB), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk

# Detection objects
DETECT_OBJS += $(MODULE)/detection/detection.o

# Skip building the following objects if a static
# module is enabled, because it already has the contents.
ifneq ($(ENABLE_GOB), STATIC_PLUGIN)
# External dependencies for detection.
DETECT_OBJS += $(MODULE)/dataio.o
endif
