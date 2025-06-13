#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <string>
#include <vector>

class AudioManager {
private:
    ALuint somTiro;
    ALuint somExplosao;
    ALuint somGameOver;
    ALuint somVitoria;
    ALuint somColisao;
    ALuint somAviso;
    
    std::vector<ALuint> fontesAtivas;
    
    void limparFontesAtivas();

public:
    AudioManager();
    ~AudioManager();
    
    bool inicializar();
    void tocarSom(ALuint buffer);
    void tocarTiro();
    void tocarExplosao();
    void tocarGameOver();
    void tocarVitoria();
    void tocarColisao();
    void tocarAviso();
    void atualizar();
};

#endif 