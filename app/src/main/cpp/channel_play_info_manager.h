//
// Created by 赵勇 on 2018/4/13.
//

#ifndef LIBFIFO_CHANNEL_PLAY_INFO_MANAGER_H
#define LIBFIFO_CHANNEL_PLAY_INFO_MANAGER_H

class ChannelPlayInfoManager {
public:
    ChannelPlayInfoManager();
    virtual ~ChannelPlayInfoManager();

    void selectStream();
    void updateInvalidSpan();
    void rewriteCdnList();

private:
    int currentAvailableStreamNum;
    int currentStreamType;
    char* currentSourceSrc;
    char* preSourceSrc;
    char* currentSourceId;
    char* preSourceId;
    void* invalidSource;
};

#endif //LIBFIFO_CHANNEL_PLAY_INFO_MANAGER_H
