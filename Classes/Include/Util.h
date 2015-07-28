#include "network\Common.h"
#include<iostream>
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

static long long GetCurSystemTime()
{
	struct cc_timeval now; 
	CCTime::gettimeofdayCocos2d(&now, NULL); 
	long long kkkk = ((long long)((long long)now.tv_sec * (long long)1000) + (long long)((long long)now.tv_usec / (long long)1000));
	return ((long long)((long long)now.tv_sec * (long long)1000) + (long long)((long long)now.tv_usec / (long long)1000)); 
}

static void stopAnimation()
{
	CCDirector::sharedDirector()->pause();
}

static void continueAnimation()
{
	CCDirector::sharedDirector()->resume();
}

static bool isPaused()
{
	return CCDirector::sharedDirector()->isPaused();
}

static CCSprite* createEdgeLabel(const char* value,float strokeValue,ccColor3B color)
{
	CCLabelTTF *label = CCLabelTTF::create(value,"Arial",30);
     
    /* ͨ��label�Ĵ�С�������������ɵ�����ͼƬ�Ĵ�С��strokeValueΪ��������ƫ������Ӱ���ϸ */
    CCSize textureSize = label->getContentSize();
    textureSize.width += 2 * strokeValue;
    textureSize.height += 2 * strokeValue;
     
    /* ���OpenGl�Ĵ���״̬ */
    glGetError();
     
    /* ����һ�������� */
    CCRenderTexture *rt = CCRenderTexture::create(textureSize.width, textureSize.height);
    if(!rt)
    {
        CCLog("create render texture failed !!!!");
        //addChild(label);
        return 0;
    }
     
    /* ������ߵ���ɫ */
    label->setColor(color);
     
    /* 
     *�õ�Դ���ֵĻ�ɫ���ƣ��洢�Ա��ָ����������µ�Ŀ���ɫ����
     *��ɫ������Ϊ��Դ��ɫ͸���ȣ�Ӱ�����ȣ���Ŀ����ɫ��Ӱ����ɫ��
     */
    ccBlendFunc originalBlend = label->getBlendFunc();
    ccBlendFunc func = { GL_SRC_ALPHA, GL_ONE};
    label->setBlendFunc(func);
     
    /* �����Զ����һЩ��������б��һ�� */
    label->setAnchorPoint(ccp(0.5, 0.5));
    //label->setRotationX(15);
     
    /* �ſ���������ʼ�滭 */
    rt->begin();
    for(int i = 0; i < 360; i += 5)//ÿ�仯5�Ȼ���һ��
    {
        float r = CC_DEGREES_TO_RADIANS(i); //������ʽ��ת��
        label->setPosition(ccp(textureSize.width * 0.5f + sin(r) * strokeValue,textureSize.height * 0.5f + cos(r) * strokeValue));
 
        /* CCRenderTexture���÷�����begin��end֮��visit���������ử��CCRenderTexture���� */
        label->visit();//����һ�θ�label
    }
 
    /* �ָ�ԭʼ��label�����������ϲ� */
    label->setColor(ccWHITE);
    label->setBlendFunc(originalBlend);
    label->setPosition(ccp(textureSize.width * 0.5f, textureSize.height * 0.5f));
    label->visit();
 
    /* �ڻ����ϻ��ƽ�������ʱ������һ������ */
    rt->end();
     
    /* ȡ�����ɵ�������ӿ���ݴ�ĥ�������� */
    CCTexture2D *texture = rt->getSprite()->getTexture();
    texture->setAntiAliasTexParameters();// setAliasTexParameters();
	CCSprite*sprite = CCSprite::createWithTexture(texture);
	sprite->setFlipX(false);
	sprite->setFlipY(true);
	return sprite;
}

	