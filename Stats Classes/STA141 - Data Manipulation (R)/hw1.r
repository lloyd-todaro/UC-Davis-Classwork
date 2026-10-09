county_class <- read.csv("CountyClassifications.csv")

people <- read.csv("People.csv")

prisoners <- read.csv("county-prison-admissions.csv")

head(county_class)

colnames(county_class)[1] <- "FIPS"

head(prisoners)

colnames(prisoners)[1] <- "FIPS"

for (i in 1:nrow(county_class)) {
  if (county_class$FIPS[i] %in% prisoners$FIPS) {
    county_class$prisoner_count[i] <- prisoners$prisoner_count[prisoners$FIPS == county_class$FIPS[i]]
  } 
  else {
    county_class$prisoner_count[i] <- NA
  }
}

