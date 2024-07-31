cypher-shell -a localhost:7687 -u neo4j -p password "MATCH (e:EMPLOYEE {ID: '$1'}) with count(e) > 0 as exist return exist"
