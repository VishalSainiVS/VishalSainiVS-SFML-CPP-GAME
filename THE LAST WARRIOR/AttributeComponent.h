#pragma once
class AttributeComponent
{
public:
	//Leveling
	
	int exp;
	int expNext;
	int attributePoints;

	//Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	bool gotReward = false;
	bool dead;
	std::string entityType;
	
	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

	int countTimeOfMaxHP = 0;
	int maxCountTimeOfMaxHP = 500;

	//Con / Des
	AttributeComponent(std::string entity_type);
	virtual ~AttributeComponent();


	

	void setRewardStatus(bool status);
	bool getRewardStatus();
	std::string getEntityType();


	//Accesors
	const int getHP();
	const int getEXP();
	void setEXP();

	//Functions
	std::string debugPrint() const;

	void loseHP(const int hp);
	
	void gainHP(const int hp);
	void gainMaxHP();
	void loseEXP(const int exp);
	void gainExp(const int exp);

	const bool isStop() const;
	const bool isDead() const;
	void setDead(bool is_dead);

	void updateStats(const bool reset);
	void updateLevel();

	void update();
};

