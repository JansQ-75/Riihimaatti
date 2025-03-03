const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const { authenticateToken } = require('./authentication');

const multer  = require('multer');
const loadedLogo = multer({dest: 'public/profilepictures/'}); //Set a destination folder

const transactionsRouter = require('./routes/transactions');
const customerRouter = require('./routes/customer');
const bank_accountRouter = require('./routes/bank_account');
const access_rightsRouter = require('./routes/access_rights');
const loginRouter = require('./routes/login');
const cardRouter = require('./routes/card');

const app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/login', loginRouter);
app.use('/transactions', authenticateToken, transactionsRouter);
app.use('/customer', authenticateToken, customerRouter);
app.use('/bank_account', authenticateToken, bank_accountRouter);
app.use('/access_rights', authenticateToken, access_rightsRouter);
app.use('/card', authenticateToken, cardRouter);
app.use((req, res) => {
  console.log(`No route matched: ${req.method} ${req.url}`);
  res.status(404).json({ error: 'Not Found' });
});
app.listen(3000);

module.exports = app;
