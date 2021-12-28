package parser

import (
	"sync"

	"github.com/the-xlang/x/lex"
	"github.com/the-xlang/x/pkg/io"
)

type ParseFileInfo struct {
	X_CXX    string
	Errors   []string
	File     *io.FILE
	Routines *sync.WaitGroup
	Parser   *Parser // Used parser.
}

// ParseFile parses file content.
func ParseFile(info *ParseFileInfo) {
	defer info.Routines.Done()
	info.X_CXX = ""
	lexer := lex.New(info.File)
	tokens := lexer.Tokenize()
	if lexer.Errors != nil {
		info.Errors = lexer.Errors
		return
	}
	info.Parser = NewParser(tokens, info)
	info.Parser.Parse()
	info.X_CXX += info.Parser.Cxx()
}
