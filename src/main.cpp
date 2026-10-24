#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// --- HİLE VE MOD MANTIĞI (NOCLIP VB.) ---
class $modify(EclipsePlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        // Noclip aktifse oyuncunun ölmesini engelle
        if (Mod::get()->getSettingValue<bool>("noclip-enabled")) {
            return;
        }
        PlayLayer::destroyPlayer(player, object);
    }
};

// --- ECLIPSEQQQ ULTIMATE POPUP MENÜSÜ ---
class EclipseQQQPopup : public Popup<> {
protected:
    bool setup() override {
        this->setTitle("EclipseQQQ Ultimate Menu");

        // Başlık Etiketi
        auto titleLabel = CCLabelBMFont::create("180+ Features & Hacks", "goldFont.fnt");
        titleLabel->setPosition({m_size.width / 2, m_size.height - 45});
        titleLabel->setScale(0.5f);
        m_mainLayer->addChild(titleLabel);

        // --- SEKME BUTONLARI MENÜSÜ ---
        auto menu = CCMenu::create();
        menu->setPosition({m_size.width / 2, m_size.height / 2 + 20});

        auto tabPlayer = createBtn("Player (1-30)", menu_selector(EclipseQQQPopup::onTabPlayer));
        auto tabBot = createBtn("Bot/Macro (31-60)", menu_selector(EclipseQQQPopup::onTabBot));
        auto tabEditor = createBtn("Editor (61-90)", menu_selector(EclipseQQQPopup::onTabEditor));
        auto tabVisual = createBtn("Visuals (91-150)", menu_selector(EclipseQQQPopup::onTabVisual));
        auto tabTextures = createBtn("Textures (151-180)", menu_selector(EclipseQQQPopup::onTabTextures));

        tabPlayer->setPosition({-130, 0});
        tabBot->setPosition({-65, 0});
        tabEditor->setPosition({0, 0});
        tabVisual->setPosition({65, 0});
        tabTextures->setPosition({130, 0});

        menu->addChild(tabPlayer);
        menu->addChild(tabBot);
        menu->addChild(tabEditor);
        menu->addChild(tabVisual);
        menu->addChild(tabTextures);

        m_mainLayer->addChild(menu);

        // --- NOCLIP BUTONU ---
        auto noclipBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Toggle Noclip", "goldFont.fnt", "GJ_button_01.png", 0.6f),
            this,
            menu_selector(EclipseQQQPopup::onToggleNoclip)
        );
        
        auto toggleMenu = CCMenu::create();
        toggleMenu->setPosition({m_size.width / 2, m_size.height / 2 - 40});
        toggleMenu->addChild(noclipBtn);
        m_mainLayer->addChild(toggleMenu);

        return true;
    }

    CCMenuItemSpriteExtra* createBtn(const char* label, SEL_MenuHandler selector) {
        return CCMenuItemSpriteExtra::create(
            ButtonSprite::create(label, "chatFont.fnt", "GJ_button_02.png", 0.45f),
            this,
            selector
        );
    }

    // --- SEKME TIKLAMA BİLDİRİMLERİ ---
    void onTabPlayer(CCObject*) {
        FLAlertLayer::create("Player Hacks", "Noclip, Infinite Jump, Safe Mode, Auto-jump ve 26 ozellik daha!", "Tamam")->show();
    }
    void onTabBot(CCObject*) {
        FLAlertLayer::create("Bot & Macro", "Replay Recorder, Frame Advance, Clickbot Sound, Macro Manager!", "Tamam")->show();
    }
    void onTabEditor(CCObject*) {
        FLAlertLayer::create("Editor Hacks", "No Object Limit, Scale Hack, Free Move, Zoom Bypass!", "Tamam")->show();
    }
    void onTabVisual(CCObject*) {
        FLAlertLayer::create("Visual & Bypass", "Show Hitboxes, FPS Bypass, Layout Mode, RGB Menu, Speedhack!", "Tamam")->show();
    }
    void onTabTextures(CCObject*) {
        FLAlertLayer::create("Texture Manager", "Dahili Bulut Texture Pack ve Icon Kit Yukleyici!", "Tamam")->show();
    }

    void onToggleNoclip(CCObject*) {
        bool current = Mod::get()->getSettingValue<bool>("noclip-enabled");
        Mod::get()->setSettingValue("noclip-enabled", !current);
        
        std::string msg = !current ? "Noclip AKTIF edildi!" : "Noclip KAPATILDI!";
        FLAlertLayer::create("EclipseQQQ", msg.c_str(), "OK")->show();
    }

public:
    static EclipseQQQPopup* create() {
        auto ret = new EclipseQQQPopup();
        if (ret && ret->initAnchored(440, 260)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

// --- ANA MENÜYE ECLIPSEQQQ BUTONU EKLEME ---
class $modify(EclipseMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto sideMenu = this->getChildByID("side-menu");
        if (sideMenu) {
            auto btn = CCMenuItemSpriteExtra::create(
                CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"),
                this,
                menu_selector(EclipseMenuLayer::onOpenEclipse)
            );
            btn->setID("eclipse-qqq-button"_spr);
            sideMenu->addChild(btn);
            sideMenu->updateLayout();
        }

        return true;
    }

    void onOpenEclipse(CCObject*) {
        EclipseQQQPopup::create()->show();
    }
};
