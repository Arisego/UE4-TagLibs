/***************************************************************************
    copyright            : (C) 2002 - 2008 by Scott Wheeler
    email                : wheeler@kde.org
 ***************************************************************************/

/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/
#include "TagLibsPrivatePCH.h"
 
#include <tstring.h>
#include <tdebug.h>

#include <oggpageheader.h>

#include "vorbisproperties.h"
#include "vorbisfile.h"

using namespace TagLib;

namespace TagLib {
	/*!
	* TagLib::Ogg::Vorbis headers can be found with one type ID byte and the string "vorbis" in
	* an Ogg stream.  0x01 indicates the setup header.
	*/
	static const char vorbisSetupHeaderID[] = { 0x01, 'v', 'o', 'r', 'b', 'i', 's', 0 };
}



namespace TagLib {

	/*
	* This is just to make this appear to be in the Ogg namespace in the
	* documentation.  The typedef below will make this work with the current code.
	* In the next BIC version of TagLib this will be really moved into the Ogg
	* namespace.
	*/

#ifdef DOXYGEN
	namespace Ogg {
#endif

		namespace Vorbis {

			class File;

			//! An implementation of audio property reading for Ogg Vorbis

			/*!
			* This reads the data from an Ogg Vorbis stream found in the AudioProperties
			* API.
			*/



			class Vorbis::Properties::PropertiesPrivate
			{
			public:
				PropertiesPrivate(File *f, ReadStyle s) :
					file(f),
					style(s),
					length(0),
					bitrate(0),
					sampleRate(0),
					channels(0),
					vorbisVersion(0),
					bitrateMaximum(0),
					bitrateNominal(0),
					bitrateMinimum(0) {}

				File *file;
				ReadStyle style;
				int length;
				int bitrate;
				int sampleRate;
				int channels;
				int vorbisVersion;
				int bitrateMaximum;
				int bitrateNominal;
				int bitrateMinimum;
			};


			////////////////////////////////////////////////////////////////////////////////
			// public members
			////////////////////////////////////////////////////////////////////////////////

			Properties::Properties(File *file, ReadStyle style) : AudioProperties(style)
			{
				d = new PropertiesPrivate(file, style);
				read();
			}

			Properties::~Properties()
			{
				delete d;
			}

			int Properties::length() const
			{
				return d->length;
			}

			int Properties::bitrate() const
			{
				return int(float(d->bitrate) / float(1000) + 0.5);
			}

			int Properties::sampleRate() const
			{
				return d->sampleRate;
			}

			int Properties::channels() const
			{
				return d->channels;
			}

			int Properties::vorbisVersion() const
			{
				return d->vorbisVersion;
			}

			int Properties::bitrateMaximum() const
			{
				return d->bitrateMaximum;
			}

			int Properties::bitrateNominal() const
			{
				return d->bitrateNominal;
			}

			int Properties::bitrateMinimum() const
			{
				return d->bitrateMinimum;
			}

			////////////////////////////////////////////////////////////////////////////////
			// private members
			////////////////////////////////////////////////////////////////////////////////

			void Properties::read()
			{
				// Get the identification header from the Ogg implementation.

				ByteVector data = d->file->packet(0);

				uint pos = 0;

				if (data.mid(pos, 7) != vorbisSetupHeaderID) {
					debug("Vorbis::Properties::read() -- invalid TagLib::Ogg::Vorbis identification header");
					return;
				}

				pos += 7;

				d->vorbisVersion = data.toUInt(pos, false);
				pos += 4;

				d->channels = uchar(data[pos]);
				pos += 1;

				d->sampleRate = data.toUInt(pos, false);
				pos += 4;

				d->bitrateMaximum = data.toUInt(pos, false);
				pos += 4;

				d->bitrateNominal = data.toUInt(pos, false);
				pos += 4;

				d->bitrateMinimum = data.toUInt(pos, false);

				// TODO: Later this should be only the "fast" mode.
				d->bitrate = d->bitrateNominal;

				// Find the length of the file.  See http://wiki.xiph.org/VorbisStreamLength/
				// for my notes on the topic.

				const Ogg::PageHeader *first = d->file->firstPageHeader();
				const Ogg::PageHeader *last = d->file->lastPageHeader();

				if (first && last) {
					long long start = first->absoluteGranularPosition();
					long long end = last->absoluteGranularPosition();

					if (start >= 0 && end >= 0 && d->sampleRate > 0)
						d->length = (int)((end - start) / (long long)d->sampleRate);
					else
						debug("Vorbis::Properties::read() -- Either the PCM values for the start or "
							"end of this file was incorrect or the sample rate is zero.");
				}
				else
					debug("Vorbis::Properties::read() -- Could not find valid first and last Ogg pages.");
			}


		}

		/*
		* To keep compatibility with the current version put Vorbis in the Ogg namespace
		* only in the docs and provide a typedef to make it work.  In the next BIC
		* version this will be removed and it will only exist in the Ogg namespace.
		*/

#ifdef DOXYGEN
	}
#else
		namespace Ogg { namespace Vorbis { typedef TagLib::AudioProperties AudioProperties; } }
#endif

}
