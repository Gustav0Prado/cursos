var statusDisplay = document.querySelector('.game--status'); //loucuras do front, possibilita a manipulação da classe '.game--status' do HTML
var PlayerSigns;
(function (PlayerSigns) {
    PlayerSigns["X"] = "X";
    PlayerSigns["O"] = "O";
})(PlayerSigns || (PlayerSigns = {}));
var gameActive;
var currentPlayer = 1;
var gameState = ["", "", "", "", "", "", "", "", ""];
var cell = [];
//arrow function para mostrar mensagem que diz qual jogador ganhou
var winningMessage = function (winner) {
    "Jogador ".concat(winner, " venceu");
};
// arrow function para mostrar mensagem quando o jogo empata       
var drawMessage = function () { return "Jogo empatou!!"; };
//arrow function para mostrar de quem é a vez
var currentPlayerTurn = function () { return "Turno do jogador ".concat(currentPlayer); };
statusDisplay.innerHTML = currentPlayerTurn(); //mostra na tela HTML alguma coisa
var winningConditions = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    [0, 4, 8],
    [2, 4, 6]
];
function handleCellPlayed(clickedCell, clickedCellIndex) {
    if (gameState[clickedCellIndex] == "") {
        cell.push(clickedCell);
        if (currentPlayer == 1) {
            gameState[clickedCellIndex] = PlayerSigns.X;
            clickedCell.innerText = PlayerSigns.X;
        }
        else if (currentPlayer == 2) {
            gameState[clickedCellIndex] = PlayerSigns.O;
            clickedCell.innerText = PlayerSigns.O;
        }
        handlePlayerChange();
        statusDisplay.innerHTML = currentPlayerTurn(); //mostra na tela HTML alguma coisa
    }
    handleResultValidation();
}
function handlePlayerChange() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}
function handleResultValidation() {
    if (cell.length >= 5) {
        var playedX_1 = "";
        var playedO_1 = "";
        gameState.forEach(function (c, index) {
            if (c == PlayerSigns.X) {
                playedX_1 += "".concat(c, ", ").concat(index, " | ");
            }
            else if (c == PlayerSigns.O) {
                playedO_1 += "".concat(c, ", ").concat(index, " | ");
            }
        });
        console.log(playedX_1);
    }
}
function handleCellClick(clickedCellEvent) {
    var clickedCell = clickedCellEvent.target;
    var clickedCellIndex = clickedCell.getAttribute('data-cell-index');
    handleCellPlayed(clickedCell, Number(clickedCellIndex));
}
function handleRestartGame() {
    gameState = ["", "", "", "", "", "", "", "", ""];
    currentPlayer = 1;
    statusDisplay.innerHTML = currentPlayerTurn();
    cell.forEach(function (c) { return c.innerText = ""; });
    cell = [];
}
document.querySelectorAll('.cell').forEach(function (cell) { return cell.addEventListener('click', handleCellClick); }); //locuras do front
document.querySelector('.game--restart').addEventListener('click', handleRestartGame); //loucuras do front
