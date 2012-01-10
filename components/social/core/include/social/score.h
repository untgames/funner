#ifndef SOCIAL_SCORE_HEADER
#define SOCIAL_SCORE_HEADER

#include <cstddef>

#include <social/collection.h>

namespace common
{

//forward declaration
class PropertyMap;

}

namespace social
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///����
///////////////////////////////////////////////////////////////////////////////////////////////////
class Score
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ���������� / �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Score ();
    Score (const void* handle);
    Score (const Score&);
    ~Score ();

    Score& operator = (const Score&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char*                PlayerId          () const;
    void                       SetPlayerId       (const char* player);
    const char*                LeaderboardId     () const;
    void                       SetLeaderboardId  (const char* leaderboard);
    const char*                UserData          () const;
    void                       SetUserData       (const char* user_data);
    double                     Value             () const;
    void                       SetValue          (double value);
    const char*                FormattedValue    () const;
    void                       SetFormattedValue (const char* formatted_value);
    size_t                     Rank              () const;
    void                       SetRank           (size_t rank);
    const common::PropertyMap& Properties        () const;
          common::PropertyMap& Properties        ();
    void                       SetProperties     (const common::PropertyMap& properties);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const void* Handle () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Score&);

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Score&, Score&);

typedef Collection<Score> ScoreList;

}

#endif
