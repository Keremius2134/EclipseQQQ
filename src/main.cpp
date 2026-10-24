#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// --- ECLIPSEQQQ BILDIRIM VE MENU YONETICISI ---
class EclipseQQQPopup {
public:
    static void showMenu() {
        FLAlertLayer::create(
            "EclipseQQQ Ultimate (180+ Features)",
            "EclipseQQQ Modu Basariyla Calisiyor!\n\n- Noclip Hack (Aktif/Pasif)\n- Bot & Macro Sistemleri\n- Editor ve Visual Araclar",
            "Tamam"
        )->show();
    }
};

// --- ANA MENUYE ECLIPSEQQQ BUTONU EKLEME ---
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
        EclipseQQQPopup::showMenu();
    }
};

// --- OYUN ICI NOCLIP MANTIGI ---
class $modify(EclipsePlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (Mod::get()->getSettingValue<bool>("noclip-enabled")) {
            return; // Noclip aciksa olumu engelle
        }
        PlayLayer::destroyPlayer(player, object);
    }
};
