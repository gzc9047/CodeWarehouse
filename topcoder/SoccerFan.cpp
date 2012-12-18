#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <vector>

struct SoccerFan
{
    struct TeamInfo
    {
        TeamInfo():
            score(0), first_lose(0x7FFFFFFF), first_draw(0x7FFFFFFF), first_win(0x7FFFFFFF)
        {}
        int score;
        int first_lose;
        int first_draw;
        int first_win;
    };
    int whereIsMistake(const std::vector<std::string>& records, const std::string& winner) {
        char team1[64], team2[64];
        int score1, score2;
        std::map<std::string, TeamInfo> team_info;
        std::map<std::string, TeamInfo> match_index;
        std::list<std::string> leader;
        int leader_score = 0;
        for (int i = 0; i < static_cast<int>(records.size()); ++i) {
            sscanf(records[i].c_str(), "%s %s %d:%d", team1, team2, &score1, &score2);
            std::string t1(team1);
            std::string t2(team2);
            std::string match_name = t1 + " " + t2;
            TeamInfo& match = match_index[match_name];
            TeamInfo& info1 = team_info[team1];
            TeamInfo& info2 = team_info[team2];
            if (score1 > score2) {
                info1.score += 3;
                info1.first_win = std::min(i, info1.first_win);
                info2.first_lose = std::min(i, info2.first_lose);
                match.first_win = std::min(i, match.first_win);
            } else if (score2 < score1) {
                info2.score += 3;
                info2.first_win = std::min(i, info2.first_win);
                info1.first_lose = std::min(i, info1.first_lose);
                match.first_lose = std::min(i, match.first_lose);
            } else {
                info1.score += 1;
                info2.score += 1;
                info2.first_draw = std::min(i, info2.first_draw);
                info1.first_draw = std::min(i, info1.first_draw);
                match.first_draw = std::min(i, match.first_draw);
            }
            if (info1.score > leader_score) {
                leader.clear();
                leader.push_back(t1);
                leader_score = info1.score;
            } else if (info1.score == leader_score) {
                leader.push_back(t1);
            }
            if (info2.score > leader_score) {
                leader.clear();
                leader.push_back(t2);
                leader_score = info2.score;
            } else if (info2.score == leader_score) {
                leader.push_back(t2);
            }
        }
        TeamInfo& winner_info = team_info[winner];
        if (leader.size() == 1) {
            if (leader.front() == winner) {
                return -2;
            } else {
                TeamInfo& leader_info = team_info[leader.front()];
                if (winner_info.score < leader_score - 3) {
                    return -1;
                } else if (winner_info.score < leader_score - 2) {
                    std::string match_name1 = winner + " " + leader.front();
                    std::string match_name2 = leader.front() + " " + winner;
                    TeamInfo& match1 = match_index[match_name1];
                    TeamInfo& match2 = match_index[match_name2];
                    if (match1.first_lose == 0x7FFFFFFF
                            && match2.first_win == 0x7FFFFFFF) {
                        return -1;
                    } else {
                        return std::min(match1.first_lose, match2.first_win);
                    }
                } else if (winner_info.score < leader_score - 1) {
                    std::string match_name1 = winner + " " + leader.front();
                    std::string match_name2 = leader.front() + " " + winner;
                    TeamInfo& match1 = match_index[match_name1];
                    TeamInfo& match2 = match_index[match_name2];
                    if (winner_info.first_lose == 0x7FFFFFFF
                            && leader_info.first_win == 0x7FFFFFFF
                            && match1.first_draw == 0x7FFFFFFF
                            && match2.first_draw == 0x7FFFFFFF) {
                        return -1;
                    } else {
                        return std::min(std::min(winner_info.first_lose, leader_info.first_win),
                                std::min(match1.first_draw, match2.first_draw));
                    }
                } else {
                    if (winner_info.first_lose == 0x7FFFFFFF
                            && winner_info.first_draw == 0x7FFFFFFF
                            && leader_info.first_win == 0x7FFFFFFF) {
                        return -1;
                    } else {
                        return std::min(std::min(winner_info.first_lose, winner_info.first_draw),
                                leader_info.first_win);
                    }
                }
            }
        } else {
            if (winner_info.score == leader_score) {
                if (leader.size() == 2) {
                    std::string leader_name;
                    if (leader.front() == winner) {
                        leader_name = leader.back();
                    } else {
                        leader_name = leader.front();
                    }
                    TeamInfo& leader_info = team_info[leader_name];
                    if (winner_info.first_lose == 0x7FFFFFFF
                            && winner_info.first_draw == 0x7FFFFFFF
                            && leader_info.first_win == 0x7FFFFFFF
                            && leader_info.first_draw == 0x7FFFFFFF) {
                        return -1;
                    } else {
                        return std::min(std::min(winner_info.first_lose, winner_info.first_draw),
                                std::min(leader_info.first_win, leader_info.first_draw));
                    }
                } else {
                    if (winner_info.first_lose == 0x7FFFFFFF
                            && winner_info.first_draw == 0x7FFFFFFF) {
                        return -1;
                    } else {
                        return std::min(winner_info.first_lose, winner_info.first_draw);
                    }
                }
            } else {
                if (winner_info.score < leader_score - 2) {
                    return -1;
                } else {
                    if (winner_info.first_lose == 0x7FFFFFFF) {
                        return -1;
                    } else {
                        return winner_info.first_lose;
                    }
                }
            }
        }
    }
};
