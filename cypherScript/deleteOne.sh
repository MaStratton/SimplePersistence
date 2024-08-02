cypher-shell -a localhost:7687 -u neo4j -p password "match (e:EMPLOYEE {ID:'$1'}) detach delete e"
