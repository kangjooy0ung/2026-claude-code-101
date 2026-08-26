function countCharacters(str) {
  return str.length;
}

function countWords(str) {
  return str.trim().split(/\s+/).filter(Boolean).length;
}

const examples = ['Hello Claude Code', '  여러   공백   포함  ', ''];

examples.forEach((str) => {
  console.log(`"${str}" -> characters: ${countCharacters(str)}, words: ${countWords(str)}`);
});

module.exports = { countCharacters, countWords };
