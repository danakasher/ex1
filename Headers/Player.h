#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

class Player{
private:
    const int id;
    int level, groupId;

public:
    Player(int id, int level, int groupId) : id(id), level(level), groupId(groupId){}
    int getId() const { return this->id; }
    int getLevel() const { return this->level; }
    void increaseLevel(int increaseBy){
        this->level += increaseBy;
    }
    //void changeGroup(int newGroupId)
    //{
      //  this->groupId=newGroupId;
    //}
    int getGroupId() const { return this->groupId; }
};

class PlayerKey{
private:
    int id;
    int level;

public:
    PlayerKey(int id, const int level): id(id), level(level){};
    bool operator==(const PlayerKey &key) const {
        return this->id == key.getId() && this->level == key.getLevel();
    }
    bool operator<(const PlayerKey &key) const {
        return this->level < key.getLevel() || (this->level == key.getLevel() && this->id > key.getId());
    }
    bool operator>(const PlayerKey &key) const {
        return !(*this < key) && !(*this == key);
    }
    void operator=(const PlayerKey &key) {
        this->id = key.getId();
        this->level = key.getLevel();

    }
    int getId() const { return this->id; }
    int getLevel() const { return this->level; }
    void setLevel(int newLevel){ this->level = newLevel; }
};

#endif //EX1_PLAYER_H
