const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const authenticateToken = require('./authentication');

const indexRouter = require('./routes/index');
const usersRouter = require('./routes/users');
const transactionsRouter = require('./routes/transactions');
const customerRouter = require('./routes/customer');
const loginRouter = require('./routes/login');
const cardRouter = require('./routes/card');


const app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/transactions', transactionsRouter);
app.use('/customer', customerRouter);
app.use('/login', loginRouter);
app.use('/card', cardRouter);

app.listen(3000);

module.exports = app;
