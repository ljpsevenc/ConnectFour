#pragma once

class Player
{
protected:
	bool offensive_;
	int choice_;

	void choose(int choice);

public:
	Player();
	explicit Player(bool offsensive);
	virtual ~Player()
	{}

	bool isOffensive() const;
	int choice() const;
	virtual void move();
};

class HumanPlayer : public Player
{
public:
	explicit HumanPlayer(bool offsensive);
	void move() override;
};

class ComputerPlayer : public Player
{
private:
	bool random_;
public:
	explicit ComputerPlayer(bool offsensive, bool random);
	void move() override;

	int evaluate(int line) const;
	static int evaluatePlayer(int line, bool offensive);

	static int ComputerPlayer::evaluateDown(int line, bool value);
	static int ComputerPlayer::evaluateHorizontal(int line, bool value);
	static int ComputerPlayer::evaluateLeftDown(int line, bool value);
	static int ComputerPlayer::evaluateRightDown(int line, bool value);
};