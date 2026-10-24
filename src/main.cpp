
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// --- OYUN İÇİ NOCLIP & HİLE MANTIĞI ---
class $modify(MyPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        // Noclip mantığı buraya bağlanacak
        PlayLayer::destroyPlayer(player, object);
    }
};

// --- ECLIPSEQQQ ULTIMATE POPUP MENUSU ---
class EclipseQQQPopup : public Popup<> {
protected:
    bool setup() override {
        // Başlık
        auto title = CCLabelBMFont::create("EclipseQQQ Ultimate (180+ Features)", "goldFont.fnt");
        title->setPosition({m_size.width / 2, m_size.height - 20});
        title->setScale(0.55f);
        this->addChild(title);

        // --- SEKME BUTONLARI ---
        auto tabPlayer = createTabButton("Player", menu_selector(EclipseQQQPopup::onTabPlayer), {-140, m_size.height / 2 - 45});
        auto tabBot = createTabButton("Bot / Macro", menu_selector(EclipseQQQPopup::onTabBot), {-70, m_size.height / 2 - 45});
        auto tabEditor = createTabButton("Editor", menu_selector(EclipseQQQPopup::onTabEditor), {0, m_size.height / 2 - 45});
        auto tabVisual = createTabButton("Visual", menu_selector(EclipseQQQPopup::onTabVisual), {70, m_size.height / 2 - 45});
        auto tabTextures = createTabButton("Textures", menu_selector(EclipseQQQPopup::onTabTextures), {140, m_size.height / 2 - 45});

        auto menu = CCMenu::create();
        menu->setPosition(m_size / 2);
        menu->addChild(tabPlayer);
        menu->addChild(tabBot);
        menu->addChild(tabEditor);
        menu->addChild(tabVisual);
        menu->addChild(tabTextures);
        this->addChild(menu);

        // --- NOCLIP TOGGLE ---
        auto noclipText = CCLabelBMFont::create("Noclip (Player Hack #1)", "chatFont.fnt");
        noclipText->setScale(0.5f);
        noclipText->setPosition({m_size.width / 2 - 80, m_size.height / 2 - 20});
        this->addChild(noclipText);

        auto noclipToggle = CCMenuItemToggle::create(
            CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png"), this, menu_selector(EclipseQQQPopup::onToggleNoclip)),
            CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png"), this, menu_selector(EclipseQQQPopup::onToggleNoclip)),
            nullptr
        );
        
        auto toggleMenu = CCMenu::create();
        toggleMenu->setPosition({m_size.width / 2 + 100, m_size.height / 2 - 20});
        toggleMenu->addChild(noclipToggle);
        this->addChild(toggleMenu);

        return true;
    }

    CCMenuItemSpriteExtra* createTabButton(const char* name, SEL_MenuHandler selector, CCPoint pos) {
        auto btn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(name, "chatFont.fnt", "GJ_button_01.png", 0.5f),
            this, selector
        );
        btn->setPosition(pos);
        return btn;
    }

    void onTabPlayer(CCObject*) {
        FLAlertLayer::create("Player Hacks (1-30)", "Noclip, Infinite Jumps, Safe Mode vb.", "Tamam")->show();
    }
    void onTabBot(CCObject*) {
        FLAlertLayer::create("Bot & Macro Replay (31-60)", "Bot Record, Playback, Clickbot Sound", "Tamam")->show();
    }
    void onTabEditor(CCObject*) {
        FLAlertLayer::create("Editor Hacks (61-90)", "Free Move, No Object Limit, Scale Hack", "Tamam")->show();
    }
    void onTabVisual(CCObject*) {
        FLAlertLayer::create("Visual & Bypass (91-120)", "FPS Bypass, Show Hitboxes, Layout Mode", "Tamam")->show();
    }
    void onTabTextures(CCObject*) {
        FLAlertLayer::create("Texture Loader (151-180)", "Dahili bulut Texture Pack yukleyicisi", "Tamam")->show();
    }

    void onToggleNoclip(CCObject*) {
        FLAlertLayer::create("EclipseQQQ", "Noclip durumu degistirildi!", "OK")->show();
    }

public:
    static EclipseQQQPopup* create() {
        auto ret = new EclipseQQQPopup();
        if (ret && ret->initAnchored(480, 320)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

// --- ANA MENUye BUTON EKLEME ---
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto sideMenu = this->getChildByID("side-menu");
        if (sideMenu) {
            auto myButton = CCMenuItemSpriteExtra::create(
                CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), 
                this, 
                menu_selector(MyMenuLayer::onOpenEclipseQQQ)
            );
            myButton->setID("eclipse-qqq-button"_spr);
            sideMenu->addChild(myButton);
            sideMenu->updateLayout();
        }

        return true;
    }

    void onOpenEclipseQQQ(CCObject*) {
        EclipseQQQPopup::create()->show();
    }
};
