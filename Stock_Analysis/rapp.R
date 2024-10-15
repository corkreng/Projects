library(shiny)
library(quantmod)
library(alphavantager)
#setwd("C:\Users\corkr\OneDrive\Documents\stock_analysis")
av_api_key("ZPOX6UIBK1L8FNJT")
api_key <- "ZPOX6UIBK1L8FNJT"
# Launches an app, with the app's source code included
ui <- fluidPage(
  # App title ----
  titlePanel("Stock Analysis"),
  # Sidebar layout with input and output definitions ----
  sidebarLayout(
    
    # Sidebar panel for inputs ----
    sidebarPanel(
      textInput("company", "Ticker :"),
      
      dateRangeInput("daterange1", "Date range:",
                   start = "2001-01-01",
                   end   = "2023-10-1"),
      actionButton("goButton", "Go!", class = "btn-success")
                   
    ),
    mainPanel(
      tabsetPanel(
        tabPanel("Info",
          plotOutput(outputId = "timeseriesplot"),
          verbatimTextOutput("info")
        ),
        tabPanel("Models" 
          
          
        ),
        tabPanel("Sentiment Analysis",
          img(src="graphic.png", height=400, width=400)
        )
      )
    )
  )
)

server <- function(input, output) {
  observeEvent(input$goButton,{
    cs <- reactive({
      # Retrieve stock data
      stock_data <- getSymbols(
        input$company,
        src = "yahoo",
        from = input$daterange1[1],
        to = input$daterange1[2],
        auto.assign = FALSE
      )
      
      # Convert the data frame to an xts object
      stock_data_xts <- as.xts(stock_data)
      
      return(stock_data_xts)
    })
    
    output$timeseriesplot <- renderPlot({
      # Check if data is available
      if (!is.null(cs())) {
        chartSeries(cs(), type = "line", name = paste(input$company, "$USD"))
      } else {
        # Display a message if data is not available
        plot(0, type = "n", main = "No Data Available")
      }
    })
     output$info<- renderPrint({ 
       if (!is.null(cs())) {
         av_get(symbol = input$company,av_fun  = "OVERVIEW",api_key = api_key)
         print(financial_data, n=46)
       } else {
         # Display a message if data is not available
         plot(0, type = "n", main = "No Data Available")
       }
      
      
     }) 
    
    
    
  })
  
}

# Run the application 
shinyApp(ui = ui, server = server)


# economic indicators should scrap 
#https://www.commerce.gov/data-and-reports/economic-indicators/dashboard
#to update an excel file within the app
# and https://towardsdatascience.com/finding-correlations-in-time-series-data-845e5dc538c4
# to find whether or the economic indicator has an statistically significant 
#effect on the stock or not
# 
#The same should be for Index's (need to look at modified index where the stock
# is excluded from the index that it is in? or equally weighted index)
# 

#competitors could be found by finviz by industry and sector


#Also, I should use FinViz to webscrap the websites of the stocks
# and add to left shoulder







