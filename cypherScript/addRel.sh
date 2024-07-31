cypher-shell -a localhost:7687 -u neo4j -p password "MATCH (eOne:EMPLOYEE {ID:'$1'}), (eTwo:EMPLOYEE {ID:'$2'}) create (eOne)-[:$3]->(eTwo), (eTwo)-[:$3]->(eOne)"
