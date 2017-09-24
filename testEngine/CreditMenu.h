#ifndef _H_CREDIT_MENU_H_
#define _H_CREDIT_MENU_H_

#include <Util\State.h>
#include <Util\StateManager.h>

class CreditMenu : public State
{
public:
	CreditMenu(StateManager *_stateManager);
	~CreditMenu();

	void Init() override;
	void CleanUp() override;

	void Pause() override;
	void Resume() override;

	void HandleEvent() override;
	void Update(float deltaTime) override;
	void Draw(SpriteBatch &batch) override;

	static CreditMenu* instance(StateManager *_stateManager) {
		if (creditInstance == NULL) {
			creditInstance = new CreditMenu(_stateManager);
		}
		return creditInstance;
	}

private:
	static CreditMenu *creditInstance;

};

#endif // !_H_CREDIT_MENU_H_
