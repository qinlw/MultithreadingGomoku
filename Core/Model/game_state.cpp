#include "game_state.h"

GameState::GameState()
    : m_status(GameStatus::NotStarted),
    m_currentPlayer(PieceColor::Black),
    m_playerRole(PlayerRole::None) {
}

GameStatus GameState::getStatus() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_status;
}

void GameState::setStatus(GameStatus status) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_status = status;
}

PieceColor GameState::getCurrentPlayer() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_currentPlayer;
}

void GameState::switchPlayer() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_currentPlayer = (m_currentPlayer == PieceColor::Black) ?
        PieceColor::White : PieceColor::Black;
}

ChessBoard& GameState::getBoard() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_board;
}

const ChessBoard& GameState::getBoard() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_board;
}

void GameState::reset() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_board.reset();
    m_status = GameStatus::Playing;
    m_currentPlayer = PieceColor::Black;
}

PlayerRole GameState::getPlayerRole() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_playerRole;
}

void GameState::setPlayerRole(PlayerRole role) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_playerRole = role;
}