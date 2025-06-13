#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager() : 
    somTiro(0), somExplosao(0), somGameOver(0), 
    somVitoria(0), somColisao(0), somAviso(0) {
}

AudioManager::~AudioManager() {
    alDeleteBuffers(1, &somTiro);
    alDeleteBuffers(1, &somExplosao);
    alDeleteBuffers(1, &somGameOver);
    alDeleteBuffers(1, &somVitoria);
    alDeleteBuffers(1, &somColisao);
    alDeleteBuffers(1, &somAviso);
    
    limparFontesAtivas();
    alutExit();
}

bool AudioManager::inicializar() {
    // Inicializa o OpenAL
    if (!alutInit(NULL, NULL)) {
        std::cerr << "Erro ao inicializar OpenAL" << std::endl;
        return false;
    }
    
    // Carrega os sons
    somTiro = alutCreateBufferFromFile("sons/tiro.wav");
    somExplosao = alutCreateBufferFromFile("sons/explosao.wav");
    somGameOver = alutCreateBufferFromFile("sons/gameover.wav");
    somVitoria = alutCreateBufferFromFile("sons/vitoria.wav");
    somColisao = alutCreateBufferFromFile("sons/colisao.wav");
    somAviso = alutCreateBufferFromFile("sons/aviso.wav");
    
    return true;
}

void AudioManager::tocarSom(ALuint buffer) {
    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    fontesAtivas.push_back(source);
}

void AudioManager::tocarTiro() {
    tocarSom(somTiro);
}

void AudioManager::tocarExplosao() {
    tocarSom(somExplosao);
}

void AudioManager::tocarGameOver() {
    tocarSom(somGameOver);
}

void AudioManager::tocarVitoria() {
    tocarSom(somVitoria);
}

void AudioManager::tocarColisao() {
    tocarSom(somColisao);
}

void AudioManager::tocarAviso() {
    tocarSom(somAviso);
}

void AudioManager::limparFontesAtivas() {
    for (ALuint source : fontesAtivas) {
        alDeleteSources(1, &source);
    }
    fontesAtivas.clear();
}

void AudioManager::atualizar() {
    // Remove fontes que já terminaram de tocar
    for (auto it = fontesAtivas.begin(); it != fontesAtivas.end();) {
        ALint estado;
        alGetSourcei(*it, AL_SOURCE_STATE, &estado);
        
        if (estado == AL_STOPPED) {
            alDeleteSources(1, &(*it));
            it = fontesAtivas.erase(it);
        } else {
            ++it;
        }
    }
} 