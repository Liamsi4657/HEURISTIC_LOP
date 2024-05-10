
#!/bin/Rscript

library(ggplot2)

correlation_plots <- function(source_path, output_path) {
    files <- list.files(source_path, pattern = "*.txt", full.names = TRUE)
    data <- array(0, c(length(files), 39))

    # Read data from files into the 'data' array
    for (i in 1:length(files)) {
        file_path <- paste(files[i], sep="")
        data[i,] <- read.table(file_path)$V4
    }

    # Create data frames for ILS and SA
    ils_data <- data[1,]
    sa_data <- data[2,]

    # Calculate min and max values for both ILS and SA
    ils_min <- min(ils_data)
    ils_max <- max(ils_data)
    sa_min <- min(sa_data)
    sa_max <- max(sa_data)

    # Fit linear regression model
    model <- lm(sa_data ~ ils_data)

    # Extract coefficients
    intercept <- coef(model)[1]
    slope <- coef(model)[2]

    print(slope)

    # Create the plot with adjusted axis limits
    plot <- ggplot() +
        geom_point(aes(x = ils_data, y = sa_data), shape = 21, color = "black", fill = "white", stroke = 0.2) +
        geom_abline(intercept = intercept, slope = slope, color = "red", linewidth = 0.2) +
        labs(x = "Relative deviation with ILS (%)", y = "Relative deviation with SA (%)") +
        ggtitle("Correlation plot")
      # Save the plot
    ggsave(filename = paste(output_path, "/correlation_plot.png", sep = ""), plot = plot)
}

correlation_plots("./statistics/experiments/", "./statistics/correlation")