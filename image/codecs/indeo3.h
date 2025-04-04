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

#include "common/scummsys.h"

/* Intel Indeo 3 decompressor, derived from ffmpeg.
 *
 * Original copyright note:
 * Intel Indeo 3 (IV31, IV32, etc.) video decoder for ffmpeg
 * written, produced, and directed by Alan Smithee
 */

#ifndef IMAGE_CODECS_INDEO3_H
#define IMAGE_CODECS_INDEO3_H

#include "image/codecs/codec.h"

namespace Image {

/**
 * Intel Indeo 3 decoder.
 *
 * Used by BMP/AVI.
 *
 * Used in video:
 *  - VMDDecoder
 */
class Indeo3Decoder : public Codec {
public:
	Indeo3Decoder(uint16 width, uint16 height, uint bitsPerPixel = 24);
	~Indeo3Decoder() override;

	const Graphics::Surface *decodeFrame(Common::SeekableReadStream &stream) override;
	Graphics::PixelFormat getPixelFormat() const override;
	bool setOutputPixelFormat(const Graphics::PixelFormat &format) override {
		if (format.bytesPerPixel != 2 && format.bytesPerPixel != 4)
			return false;
		_pixelFormat = format;
		return true;
	}

	static bool isIndeo3(Common::SeekableReadStream &stream);

private:
	Graphics::Surface *_surface;

	uint16 _width;
	uint16 _height;
	Graphics::PixelFormat _pixelFormat;

	static const byte _corrector_type_0[24];
	static const byte _corrector_type_2[8];
	static const uint32 correction[];
	static const uint32 correctionloworder[];
	static const uint32 correctionhighorder[];

	struct YUVBufs {
		byte *Ybuf;
		byte *Ubuf;
		byte *Vbuf;
		byte *the_buf;
		uint32 the_buf_size;
		uint16 y_w, y_h;
		uint16 uv_w, uv_h;
	};

	YUVBufs _iv_frame[2];
	YUVBufs *_cur_frame;
	YUVBufs *_ref_frame;

	byte *_ModPred;
	byte *_corrector_type;

	void buildModPred();
	void allocFrames();

	void decodeChunk(byte *cur, byte *ref, int width, int height,
			const byte *buf1, uint32 fflags2, const byte *hdr,
			const byte *buf2, int min_width_160);
};

} // End of namespace Image

#endif
