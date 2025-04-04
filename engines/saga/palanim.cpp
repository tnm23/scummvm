/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// Palette animation module
#include "saga/saga.h"
#include "saga/gfx.h"

#include "saga/events.h"

#include "saga/palanim.h"
#include "saga/interface.h"

namespace Saga {

PalAnim::PalAnim(SagaEngine *vm) : _vm(vm) {
}

void PalAnim::loadPalAnim(const ByteArray &resourceData) {

	clear();

	if (resourceData.empty()) {
		return;
	}

	ByteArrayReadStreamEndian readS(resourceData, _vm->isBigEndian());

	if (_vm->getGameId() == GID_IHNM) {
		return;
	}

	_entries.resize(readS.readUint16());

	debug(3, "PalAnim::loadPalAnim(): Loading %d PALANIM entries.", _entries.size());

	for (auto &palAnimEntry : _entries) {

		palAnimEntry.cycle = 0;

		palAnimEntry.colors.resize(readS.readUint16());
		debug(2, "PalAnim::loadPalAnim(): Loading %d SAGA_COLOR structures.", palAnimEntry.colors.size());

		palAnimEntry.palIndex.resize(readS.readUint16());
		debug(2, "PalAnim::loadPalAnim(): Loading %d palette indices.\n", palAnimEntry.palIndex.size());


		for (uint j = 0; j < palAnimEntry.palIndex.size(); j++) {
			palAnimEntry.palIndex[j] = readS.readByte();
		}

		for (auto &color : palAnimEntry.colors) {
			color.red = readS.readByte();
			color.green = readS.readByte();
			color.blue = readS.readByte();
		}
	}
}

void PalAnim::cycleStart() {
	Event event;

	if (_entries.empty()) {
		return;
	}

	event.type = kEvTOneshot;
	event.code = kPalAnimEvent;
	event.op = kEventCycleStep;
	event.time = PALANIM_CYCLETIME;
	_vm->_events->queue(event);
}

void PalAnim::cycleStep(int vectortime) {
	static PalEntry pal[256];
	uint16 palIndex;
	uint16 colIndex;

	uint16 j;
	uint16 cycle;
	uint16 cycleLimit;

	Event event;

	if (_entries.empty()) {
		return;
	}

	_vm->_gfx->getCurrentPal(pal);

	for (auto &palAnimEntry : _entries) {
		cycle = palAnimEntry.cycle;
		cycleLimit = palAnimEntry.colors.size();
		for (j = 0; j < palAnimEntry.palIndex.size(); j++) {
			palIndex = palAnimEntry.palIndex[j];
			colIndex = (cycle + j) % cycleLimit;
			pal[palIndex].red = (byte) palAnimEntry.colors[colIndex].red;
			pal[palIndex].green = (byte) palAnimEntry.colors[colIndex].green;
			pal[palIndex].blue = (byte) palAnimEntry.colors[colIndex].blue;
		}

		palAnimEntry.cycle++;

		if (palAnimEntry.cycle == cycleLimit) {
			palAnimEntry.cycle = 0;
		}
	}

	// Don't cycle the palette when the map is open
	// Fixes bug #3636 - "ITE: Glitch when looking at the map while at the docks"
	if (_vm->_interface->getMode() != kPanelMap)
		_vm->_gfx->setPalette(pal);

	event.type = kEvTOneshot;
	event.code = kPalAnimEvent;
	event.op = kEventCycleStep;
	event.time = vectortime + PALANIM_CYCLETIME;
	_vm->_events->queue(event);

}

void PalAnim::clear() {
	debug(3, "PalAnim::clear()");

	_entries.clear();
}

} // End of namespace Saga
