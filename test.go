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

// func random_values()
// {

// }

func boolToInt(b bool) int {
    if b {
        return 1
    }
    return 0
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
   
    var q int = rand.Intn(20)
    fmt.Println(q)

    matrix := make([][]pvalue, q)
    for i := range matrix {
        matrix[i] = make([]pvalue, q)
        for j := range matrix[i] {
            matrix[i][j].index = i*q + j
            matrix[i][j].compound = '*'
            matrix[i][j].hydrophobic = true
        }
    }

    
    matrix = random_values(matrix)

    printMatrix(matrix)

}