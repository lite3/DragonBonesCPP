#ifndef DEMO_TEST_H
#define DEMO_TEST_H

#include "Demo.h"

#include "ui/CocosGUI.h"
using namespace ui;

USING_NS_DB;

class DemoTest : public DemoBase
{
public:
    CREATE_FUNC(DemoTest);
    DemoTest();
    ~DemoTest();
    virtual std::string title();
    virtual std::string subtitle();

protected:
    virtual void demoInit() override;
	virtual void addInteraction() override;

private:
	void touchEvent(Ref *pSender, Widget::TouchEventType type);

private:
    DBCCArmatureNode *_armatureNode;
};

#endif // DEMO_CHASE_STARLING_H
