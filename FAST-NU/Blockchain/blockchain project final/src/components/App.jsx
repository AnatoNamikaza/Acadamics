import React from 'react';
import { hot } from 'react-hot-loader';
import { BrowserRouter as Router, Route } from 'react-router-dom';
import { Layout, Menu, Input } from 'antd';
import Home from './home';
import YourOrders from './your-orders';
import AddProduct from './add-product';
import About from './about';
import MenuLink from './menu-link';
import logo from '../images/logo.svg';
import styles from './app.scss';

const { Header, Content, Footer } = Layout;
const { Search } = Input;

const App = () => (
  <Router>
    <Layout className={styles.app}>
      <Header>
        <img className={styles.logo} src={logo} alt="logo" />
        <Search
          className={styles.search}
          placeholder="What are you looking for..."
        />
      </Header>

      <Content className={styles.content}>
        <Menu
          className={styles.mainNav}
          mode="horizontal"
          defaultSelectedKeys={['active']}
          selectable={false}
        >
          <MenuLink to="/" activeOnlyWhenExact label="Home" />
          <MenuLink to="/your-orders" label="Your Orders" />
          <MenuLink to="/add-product" label="Add Product" />
          <MenuLink to="/about" label="About" />
        </Menu>

        <div className={styles.main}>
          <Route exact path="/" component={Home} />
          <Route path="/your-orders" component={YourOrders} />
          <Route path="/add-product" component={AddProduct} />
          <Route path="/about" component={About} />
        </div>
      </Content>

      <Footer className={styles.footer}>
        DApp Store ©2018 Created by Nha Hoang
      </Footer>
    </Layout>
  </Router>
);

export default hot(module)(App);
