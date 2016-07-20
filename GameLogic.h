#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
struct GameLogic
{
	GameLogic() : m_blockSize(25), m_gameWinningScore(3) {}

	int m_gameWinningScore;
	int m_blockSize;
};
#endif // !GAME_LOGIC_H