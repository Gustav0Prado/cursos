const statusDisplay: Element = document.querySelector('.game--status')!; //loucuras do front, possibilita a manipulação da classe '.game--status' do HTML

enum PlayerSigns {
    X = "X",
    O = "O"
}

let gameActive: true
let currentPlayer: number = 1
let gameState: string[] = ["", "", "", "", "", "", "", "", ""];
let cell: HTMLElement[] = [];

//arrow function para mostrar mensagem que diz qual jogador ganhou
const winningMessage = (winner:Number) : void =>{
    `Jogador ${winner} venceu`
}

// arrow function para mostrar mensagem quando o jogo empata       
const drawMessage: () => string = () => `Jogo empatou!!`

//arrow function para mostrar de quem é a vez
const currentPlayerTurn: () => string = () => `Turno do jogador ${currentPlayer}`

statusDisplay.innerHTML = currentPlayerTurn(); //mostra na tela HTML alguma coisa

const winningConditions: number[][] = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    [0, 4, 8],
    [2, 4, 6]
];

function handleCellPlayed(clickedCell: HTMLElement, clickedCellIndex: number): void {
    if(gameState[clickedCellIndex] == ""){
        cell.push(clickedCell)

        if (currentPlayer == 1){
            gameState[clickedCellIndex] = PlayerSigns.X;
            clickedCell.innerText = PlayerSigns.X;
        }
        else if (currentPlayer == 2){
            gameState[clickedCellIndex] = PlayerSigns.O;
            clickedCell.innerText = PlayerSigns.O;
        }
        handlePlayerChange();
        statusDisplay.innerHTML = currentPlayerTurn(); //mostra na tela HTML alguma coisa
    }
    handleResultValidation();
}

function handlePlayerChange(): void {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

function handleResultValidation(): void {
    if(cell.length >= 5){
        let playedX: string = "";
        let playedO: string = "";
        gameState.forEach((c, index) => {
            if(c == PlayerSigns.X){
                playedX += `${c}, ${index} | `
            }
            else if(c == PlayerSigns.O){
                playedO += `${c}, ${index} | `
            }
        })
        console.log(playedX)
    }
}

function handleCellClick(clickedCellEvent: Event) {
    const clickedCell: HTMLElement = <HTMLElement>clickedCellEvent.target;
    const clickedCellIndex: string | null = clickedCell.getAttribute('data-cell-index');

   handleCellPlayed(clickedCell, Number(clickedCellIndex));
}

function handleRestartGame() {
    gameState = ["", "", "", "", "", "", "", "", ""];
    currentPlayer = 1;
    statusDisplay.innerHTML = currentPlayerTurn();

    cell.forEach(c => c.innerText = "");
    cell = [];
}

document.querySelectorAll('.cell').forEach(cell => cell.addEventListener('click', handleCellClick)); //locuras do front
document.querySelector('.game--restart')!.addEventListener('click', handleRestartGame); //loucuras do front