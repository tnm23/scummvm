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

#ifndef COMMON_ERROR_H
#define COMMON_ERROR_H

#include "common/str.h"

namespace Common {

/**
 * @defgroup common_error Error codes
 * @ingroup common
 *
 * @brief  Commonly used error codes.
 *
 * @{
 */

/**
 * Error codes that may be reported by plugins under various circumstances.
 *
 * @note Error names should follow the pattern k-NOUN/ACTION-CONDITION-Error.
 *       So kPathInvalidError is correct, but the following are not:
 *       kInvalidPath, kPathInvalid, kPathIsInvalid, kInvalidPathError.
 *
 * @todo Adjust all error codes to comply with these conventions.
 */
enum ErrorCode {
	kNoError = 0,					///< No error occurred.

	kNoGameDataFoundError,			///< Engine initialization: No game data was found in the specified location.
	kUnsupportedGameidError,		///< Engine initialization: Game ID not supported by this (Meta)Engine.
	kUnsupportedColorMode,			///< Engine initialization: Engine does not support backend's color mode.
	kAudioDeviceInitFailed,			///< Engine initialization: Audio device initialization failed.

	kReadPermissionDenied,			///< Unable to read data due to missing read permission.
	kWritePermissionDenied,			///< Unable to write data due to missing write permission.

	kPathDoesNotExist,				///< The specified path does not exist.
	kPathNotDirectory,				///< The specified path does not point to a directory.
	kPathNotFile,					///< The specified path does not point to a file.

	kCreatingFileFailed,			///< Failed creating a (savestate) file.
	kReadingFailed,					///< Failed to read a file (permission denied?).
	kWritingFailed,					///< Failure to write data - disk full?

	kMetaEnginePluginNotFound,		///< Failed to find a MetaEnginePlugin.
	kEnginePluginNotFound,			///< Failed to find an Engine plugin to handle target.
	kEnginePluginNotSupportSaves,	///< The plugin does not support listing save states.

	kUserCanceled,					///< User has canceled the launching of the game.

	kUnknownError					///< Catch-all error, used if no other error code matches.
};

/**
 * An Error instance pairs an error code with string description providing more
 * details about the error. For every error code, a default description is
 * provided, but it is possible to optionally augment that description with
 * extra information when creating a new Error instance.
 */
class Error {
protected:
	ErrorCode _code; /*!< Error code. */
	String _desc;    /*!< Error description. */
public:
	/**
	 * Construct a new Error with the specified error code and the default
	 * error message.
	 */
	Error(ErrorCode code = kUnknownError);

	/**
	 * Construct a new Error with the specified error code and an augmented
	 * error message. Specifically, the provided extra text is suitably
	 * appended to the default message.
	 */
	Error(ErrorCode code, const String &extra);

	/**
	 * Get the untranslated description of this error.
	 */
	String getDesc() const;

	/**
	 * Get the translated description of this error.
	 */
	U32String getTranslatedDesc() const;

	/**
	 * Get the error code of this error.
	 */
	ErrorCode getCode() const { return _code; }
};

/** @} */

} // End of namespace Common

#endif //COMMON_ERROR_H
