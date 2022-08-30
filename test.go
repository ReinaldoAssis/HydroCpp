package main

import (
	"fmt"
	"math/rand"
	"time"
)

type pvalue struct
{
    index int
    compound byte
    hydrophobic bool
}

func boolToInt(b bool) int {
    if b {
        return 1
    }
    return 0
}

func generateOddNumber() int {
    var n int = rand.Intn(20)
    if n % 2 == 0 {
        n++
    }
    return n
}

func findCenter (matrix [][]pvalue) (int, int) {
    var center_x, center_y int = len(matrix)/2, len(matrix[0])/2
    return center_x, center_y
}

func placeAtPosition(matrix [][]pvalue, x int, y int, element pvalue) {
    matrix[x][y] = element
}

func printMatrix(matrix [][]pvalue) {
    for i := range matrix {
        for j := range matrix[i] {
            fmt.Printf("%c ", matrix[i][j].compound)
        }
        fmt.Println()
    }
}

func random_values(matrix [][]pvalue) [][]pvalue {
    for i := range matrix {
        for j := range matrix[i] {
            var chance int = rand.Intn(100)

            if chance >= 50 {
                matrix[i][j].compound = byte(rand.Intn(26) + 65)
            }
            matrix[i][j].hydrophobic = bool(rand.Intn(2) == 1)
        }
    }
    return matrix
}

func main() {
    
    fmt.Println("Hi mom hi dad")
    rand.Seed(time.Now().UnixNano())
   
    var q int = generateOddNumber()
    var s int = generateOddNumber()

    fmt.Printf("%d x %d\n",q,s)

    matrix := make([][]pvalue, q)
    for i := range matrix {
        matrix[i] = make([]pvalue, s)
        for j := range matrix[i] {
            matrix[i][j].index = i*q + j
            matrix[i][j].compound = '*'
            matrix[i][j].hydrophobic = true
        }
    }

    
    //matrix = random_values(matrix)

    var center_x, center_y int = findCenter(matrix)
    placeAtPosition(matrix, center_x, center_y, pvalue{index: 0, compound: 'A', hydrophobic: true})

    printMatrix(matrix)

}