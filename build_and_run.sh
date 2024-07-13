if command -v clang; then
    echo "compiling with clang..."
    if clang vocabbot.c -o vocabbot; then
        ./vocabbot
    else
        echo "compiling with clang failed"
    fi
elif command -v gcc; then
    echo "compiling with gcc.."
    if gcc vocabbot.c -o vocabbot; then
        ./vocabbot
    else
        echo "compiling with gcc failed"
    fi
fi
