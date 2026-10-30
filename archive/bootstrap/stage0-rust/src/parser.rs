use pest_derive::Parser;

#[derive(Parser)]
#[grammar = "grammar/bunker.pest"]
pub struct BunkerParser;
