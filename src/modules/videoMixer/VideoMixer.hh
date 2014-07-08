/*
 *  VideoMixer - Video mixer structure
 *  Copyright (C) 2014  Fundació i2CAT, Internet i Innovació digital a Catalunya
 *
 *  This file is part of media-streamer.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Authors:  Marc Palau <marc.palau@i2cat.net>
 */
 
#ifndef _VIDEO_MIXER_HH
#define _VIDEO_MIXER_HH

#include "../../VideoFrame.hh"
#include "../../Filter.hh"
#include <opencv/cv.hpp>
 

#define MAX_LAYERS 8
#define VMIXER_MAX_CHANNELS 8

class ChannelConfig {

public:
    ChannelConfig(int width, int height, int x, int y, int layer);
    void config(int width, int height, int x, int y, int layer, bool enabled);

    int getWidth() {return width;};
    int getHeight() {return height;};
    int getX() {return x;};
    int getY() {return y;};
    int getLayer() {return layer;};
    bool isEnabled() {return enabled;};

private:
    int width;
    int height;
    int x;
    int y;
    int layer;
    bool enabled;
};

class VideoMixer : public ManyToOneFilter {
    
    public:
        VideoMixer(int inputChannels = VMIXER_MAX_CHANNELS);
        VideoMixer(int inputChannels, int outputWidth, int outputHeight);
        FrameQueue *allocQueue(int wId);
        bool doProcessFrame(std::map<int, Frame*> orgFrames, Frame *dst);

    protected:
        Reader *setReader(int readerID, FrameQueue* queue);
        void initializeEventMap();
        void doGetState(Jzon::Object &filterNode);

    private:
        void pasteToLayout(int frameID, VideoFrame* vFrame);
        bool configChannel(int id, float width, float height, float x, float y, int layer, bool enabled);

        void configChannelEvent(Jzon::Node* params, Jzon::Object &outputNode); 

        std::map<int, ChannelConfig*> channelsConfig;        
        int outputWidth;
        int outputHeight;
        cv::Mat layoutImg;
        int maxChannels;
};


#endif